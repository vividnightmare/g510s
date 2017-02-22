/*
 *  This file is part of g510s.
 *
 *  g510s is  free  software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published by
 *  the  Free Software Foundation; either version 3 of the License, or (at your
 *  option)  any later version.
 *
 *  g510s is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with g510s; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1335  USA
 *
 *  Copyright © 2015 John Augustine
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <libg15.h>
#include <libappindicator/app-indicator.h>

#include "g510s.h"


extern AppIndicator *indicator;

void *lcd_client_function(void *display) {
  lcdnode_t *g15node = display;
  lcd_t *client_lcd = g15node->lcd;
  int retval;
  unsigned int width, height, buflen, header = 4;
  
  int client_sock = client_lcd->connection;
  char helo[] = SERV_HELO;
  unsigned char *tmpbuf = malloc(6880);
  
  connected_clients++;
  
  if (g15_send(client_sock, (char*)helo, strlen(SERV_HELO)) < 0) {
    goto exitthread;
  }
  
  if (g15_recv(g15node, client_sock, (char*)tmpbuf, 4) < 4) {
    goto exitthread;
  }
  
  if (tmpbuf[0] == 'G') {
    while (leaving == 0) {
      retval = g15_recv(g15node, client_sock, (char *)tmpbuf, 6880);
      if (retval != 6880) {
        break;
      }
      //pthread_mutex_lock(&lcdlist_mutex);
      memset(client_lcd->buf, 0, 1024);
      convert_buf(client_lcd, tmpbuf);
      client_lcd->ident = random();
      //pthread_mutex_unlock(&lcdlist_mutex);
    }
  } else if (tmpbuf[0] == 'R') {
    while (leaving == 0) {
      retval = g15_recv(g15node, client_sock, (char *)tmpbuf, 1048);
      if (retval != 1048) {
        break;
      }
      //pthread_mutex_lock(&lcdlist_mutex);
      memcpy(client_lcd->buf, tmpbuf, sizeof(client_lcd->buf));
      client_lcd->ident = random();
      //pthread_mutex_unlock(&lcdlist_mutex);
    }
  } else if (tmpbuf[0] == 'W') {
    while (leaving == 0) {
      retval = g15_recv(g15node, client_sock, (char*)tmpbuf, 865);
      if (!retval) {
        break;
      }
      
      if (tmpbuf[2] & 1) {
        width = ((unsigned char)tmpbuf[2] ^ 1) | (unsigned char)tmpbuf[3];
        height = tmpbuf[4];
        header = 5;
      } else {
        width = tmpbuf[2];
        height = tmpbuf[3];
        header = 4;
      }
      
      buflen = (width / 8) * height;
      
      if (buflen > 860) {
        retval = g15_recv(g15node, client_sock, NULL, buflen-860);
        buflen = 860;
      }
      
      if (width != 160) {
        goto exitthread;
      }
      
      //pthread_mutex_lock(&lcdlist_mutex);
      memcpy(client_lcd->buf, tmpbuf + header, buflen + header);
      client_lcd->ident = random();
      //pthread_mutex_unlock(&lcdlist_mutex);
    }
  }
  exitthread:
    close(client_sock);
    free(tmpbuf);
    lcdnode_remove(display);
    connected_clients--;
    pthread_exit(NULL);
}

void *key_function(void *lcdlist) {
  int keyreturn = 0;
  unsigned int key = 0;
  static unsigned int key_state = 0;
  lcdlist_t *displaylist = (lcdlist_t*)(lcdlist);
  
  while (!leaving) {
    if (device_found) {
      keyreturn = getPressedKeys(&key, 0);
      
      // dont process normal keys
      while (keyreturn == G15_ERROR_TRY_AGAIN) {
        keyreturn = getPressedKeys(&key, 0);
      }
      
      // process extra keys
      if ((keyreturn == G15_NO_ERROR) && (key != key_state)) {
        current_key_state = key;
        process_keys(displaylist, key, key_state);
        key_state = key;
      }
      
      // handle hotplugging of keyboard or sound devices
      if (keyreturn == -ENODEV) {
        device_found = 0;
        app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ATTENTION);
        exit_uinput();
        exitLibG15();
        while (!device_found) {
          printf("G510s: device disconnected, retrying...\n");
          if (setupLibG15(0x46d, 0xc22d, 0) == G15_NO_ERROR) {
            printf("G510s: found device 046d:c22d\n");
            device_found = 1;
          } else if (setupLibG15(0x46d, 0xc22e, 0) == G15_NO_ERROR) {
            printf("G510s: found device 046d:c22e\n");
            device_found = 1;
          }
          sleep(1);
        }
        if (init_uinput() != 0) {
          printf("G510s: failed to initialize uinput, media keys not available\n");
        }
        set_mkey_state(g510s_data.mkey_state);
        if (displaylist->tail == displaylist->current) {
          displaylist->current->lcd->ident = 0;
        }
        app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
      }
    } else { // device was not found
      // wait for a device
      while (!device_found) {
        printf("G510s: waiting for device...\n");
        if (setupLibG15(0x46d, 0xc22d, 0) == G15_NO_ERROR) {
          printf("G510s: found device 046d:c22d\n");
          device_found = 1;
        } else if (setupLibG15(0x46d, 0xc22e, 0) == G15_NO_ERROR) {
          printf("G510s: found device 046d:c22e\n");
          device_found = 1;
        }
        sleep(1);
      }
      if (init_uinput() != 0) {
        printf("G510s: failed to initialize uinput, media keys not available\n");
      }
      set_mkey_state(g510s_data.mkey_state);
      if (displaylist->tail == displaylist->current) {
        displaylist->current->lcd->ident = 0;
      }
      app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    }
  }
  return NULL;
}

void *update_function(void *lcdlist) {
  lcdlist_t *displaylist = (lcdlist_t*)(lcdlist);
  static long int lastlcd = 1;
  
  lcd_t *displaying = displaylist->tail->lcd;
  memset(displaying->buf, 0, 1024);
  displaying->ident = 0;
  
  while (!leaving) {
    if (device_found) {
      // only update the color if the changes will be visible
      if (update == g510s_data.mkey_state) {
        switch (g510s_data.mkey_state) {
          case 1:
            setG510LEDColor(g510s_data.m1.red, g510s_data.m1.green, g510s_data.m1.blue);
            break;
          case 2:
            setG510LEDColor(g510s_data.m2.red, g510s_data.m2.green, g510s_data.m2.blue);
            break;
          case 3:
            setG510LEDColor(g510s_data.m3.red, g510s_data.m3.green, g510s_data.m3.blue);
            break;
          case 4:
            setG510LEDColor(g510s_data.mr.red, g510s_data.mr.green, g510s_data.mr.blue);
            break;
          default:
            printf("G510s: invalide mkey_state!!\n");
            break;
        }
        update = 0;
      }
      
      displaying = displaylist->current->lcd;
      
      if (displaylist->tail == displaylist->current) {
        digital_clock(displaying);
      }
      
      if (displaying->ident != lastlcd) {
        writePixmapToLCD(displaying->buf);
        lastlcd = displaying->ident;
      }
      
      // we dont do anything here
      if (displaying->state_changed) {
        displaying->state_changed = 0;
      }
    }
    usleep(50000);
  }
  return NULL;
}

void *server_function(void *lcdlist) {
  lcdlist_t *displaylist = (lcdlist_t*)(lcdlist);
  int g15_socket = -1;
  
  if ((g15_socket = init_sockserver()) < 0) {
    printf("G510s: unable to initialise server at port %i\n", LISTEN_PORT);
    return NULL;
  }
  
  if (fcntl(g15_socket, F_SETFL, O_NONBLOCK) < 0) {
    printf("G510s: unable to set socket to nonblocking\n");
  }
  
  while (!leaving) {
    client_connect(&displaylist, g15_socket);
  }
  
  close(g15_socket);
  return NULL;
}