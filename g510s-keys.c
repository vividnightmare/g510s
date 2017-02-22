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
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <pthread.h>
#include <libg15.h>

#include "g510s.h"


static int uinp_fd = -1;

int init_uinput() {
  int i = 0;
  struct uinput_user_dev uinp;
  static const char *uinput_device_fn[] = { "/dev/uinput", "/dev/input/uinput", "/dev/misc/uinput", 0 };
  
  while (uinput_device_fn[i] && (uinp_fd = open(uinput_device_fn[i], O_RDWR)) < 0) {
    ++i;
  }
  
  if (uinp_fd < 0) {
    printf("G510s: failed to open uinput\n");
    return -1;
  }
  
  memset(&uinp, 0, sizeof(uinp));
  strncpy(uinp.name, "G15 Extra Keys", UINPUT_MAX_NAME_SIZE);
  
  uinp.id.version = 4;
  uinp.id.bustype = BUS_USB;
  
  ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
  
  for (i = 0; i < 256; ++i) {
    ioctl(uinp_fd, UI_SET_KEYBIT, i);
  }
  
  write(uinp_fd, &uinp, sizeof(uinp));
  
  if (ioctl(uinp_fd, UI_DEV_CREATE)) {
    printf("G510s: failed to create uinput device\n");
    return -1;
  }
  
  return 0;
}

void exit_uinput() {
  ioctl(uinp_fd, UI_DEV_DESTROY);
  close(uinp_fd);
}

void uinput_keydown(unsigned char code) {
  struct input_event event;
  
  memset(&event, 0, sizeof(event));
  event.type = EV_KEY;
  event.code = code;
  event.value = 1;
  write(uinp_fd, &event, sizeof(event));
  
  memset(&event, 0, sizeof(event));
  event.type = EV_SYN;
  event.code = SYN_REPORT;
  write(uinp_fd, &event, sizeof(event));
}

void uinput_keyup(unsigned char code) {
  struct input_event event;
  
  memset(&event, 0, sizeof(event));
  event.type = EV_KEY;
  event.code = code;
  event.value = 0;
  write(uinp_fd, &event, sizeof(event));
  
  memset(&event, 0, sizeof(event));
  event.type = EV_SYN;
  event.code = SYN_REPORT;
  write(uinp_fd, &event, sizeof(event));
}

void process_keys(lcdlist_t *displaylist, unsigned int key, unsigned int key_state) {

  /*
   * Handle Extended Multimedia Keys
   */
  
  if ((key & G15_KEY_PLAY) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_PLAY) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_PLAYPAUSE);
  }
  if (!(key & G15_KEY_PLAY) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_PLAY) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_PLAYPAUSE);
  }
  if ((key & G15_KEY_STOP) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_STOP) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_STOPCD);
  }
  if (!(key & G15_KEY_STOP) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_STOP) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_STOPCD);
  }
  if ((key & G15_KEY_NEXT) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_NEXT) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_NEXTSONG);
  }
  if (!(key & G15_KEY_NEXT) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_NEXT) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_NEXTSONG);
  }
  if ((key & G15_KEY_PREV) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_PREV) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_PREVIOUSSONG);
  }
  if (!(key & G15_KEY_PREV) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_PREV) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_PREVIOUSSONG);
  }
  if ((key & G15_KEY_MUTE) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_MUTE) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_MUTE);
  }
  if (!(key & G15_KEY_MUTE) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_MUTE) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_MUTE);
  }
  if ((key & G15_KEY_RAISE_VOLUME) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_RAISE_VOLUME) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_VOLUMEUP);
  }
  if (!(key & G15_KEY_RAISE_VOLUME) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_RAISE_VOLUME) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_VOLUMEUP);
  }
  if ((key & G15_KEY_LOWER_VOLUME) && (key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_LOWER_VOLUME) && !(key_state & G15_EXTENDED_KEY)) {
    uinput_keydown(KEY_VOLUMEDOWN);
  }
  if (!(key & G15_KEY_LOWER_VOLUME) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_LOWER_VOLUME) && (key_state & G15_EXTENDED_KEY)) {
    uinput_keyup(KEY_VOLUMEDOWN);
  }
  
  /*
   * Handle Light Key
   */
  
  if ((key & G15_KEY_LIGHT) && !(key_state & G15_KEY_LIGHT)) {
    // color wont set if backlight is off
    // to workaround we set the color whenever we toggle the backlight
    set_color();
  }
  if (!(key & G15_KEY_LIGHT) && (key_state & G15_KEY_LIGHT)) {
    
  }
  
  /*
   * Handle M-Keys
   */
  
  if ((key & G15_KEY_M1) && !(key_state & G15_KEY_M1)) {
    set_mkey_state(1);
  }
  if (!(key & G15_KEY_M1) && (key_state & G15_KEY_M1)) {
    
  }
  if ((key & G15_KEY_M2) && !(key_state & G15_KEY_M2)) {
    set_mkey_state(2);
  }
  if (!(key & G15_KEY_M2) && (key_state & G15_KEY_M2)) {
    
  }
  if ((key & G15_KEY_M3) && !(key_state & G15_KEY_M3)) {
    set_mkey_state(3);
  }
  if (!(key & G15_KEY_M3) && (key_state & G15_KEY_M3)) {
    
  }
  if ((key & G15_KEY_MR) && !(key_state & G15_KEY_MR)) {
    set_mkey_state(4);
  }
  if (!(key & G15_KEY_MR) && (key_state & G15_KEY_MR)) {
    
  }
  
  /*
   * Handle L-Keys
   */
  
  if ((key & G15_KEY_L1) && !(key_state & G15_KEY_L1)) {
    //pthread_mutex_lock(&lcdlist_mutex);
    if (displaylist->tail == displaylist->current) {
      displaylist->current = displaylist->head;
    } else {
      displaylist->current = displaylist->current->prev;
    }
    displaylist->current->lcd->usr_foreground = 1;
    displaylist->current->lcd->state_changed = 1;
    displaylist->current->last_priority = displaylist->current;
    //pthread_mutex_unlock(&lcdlist_mutex);
  }
  if (!(key & G15_KEY_L1) && (key_state & G15_KEY_L1)) {
    
  }
  if ((key & G15_KEY_L2) && !(key_state & G15_KEY_L2)) {
    if (displaylist->tail == displaylist->current) {
      if (!g510s_data.clock_mode) {
        g510s_data.clock_mode = 1;
      } else {
        g510s_data.clock_mode = 0;
      }
      displaylist->current->lcd->ident = 0;
    } else {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if (!(key & G15_KEY_L2) && (key_state & G15_KEY_L2)) {
    if (displaylist->tail != displaylist->current) {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if ((key & G15_KEY_L3) && !(key_state & G15_KEY_L3)) {
    if (displaylist->tail == displaylist->current) {
      if (!g510s_data.show_date) {
        g510s_data.show_date = 1;
      } else {
        g510s_data.show_date = 0;
      }
      displaylist->current->lcd->ident = 0;
    } else {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if (!(key & G15_KEY_L3) && (key_state & G15_KEY_L3)) {
    if (displaylist->tail != displaylist->current) {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if ((key & G15_KEY_L4) && !(key_state & G15_KEY_L4)) {
    if (displaylist->tail != displaylist->current) {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if (!(key & G15_KEY_L4) && (key_state & G15_KEY_L4)) {
    if (displaylist->tail != displaylist->current) {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if ((key & G15_KEY_L5) && !(key_state & G15_KEY_L5)) {
    if (displaylist->tail != displaylist->current) {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  if (!(key & G15_KEY_L5) && (key_state & G15_KEY_L5)) {
    if (displaylist->tail != displaylist->current) {
      send_keystate(displaylist->current->lcd, key);
    }
  }
  
  /*
   * Handle Extended G-Keys
   */
  
  if ((key & G15_KEY_G1) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G1) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(1);
  }
  if (!(key & G15_KEY_G1) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G1) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G2) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G2) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(2);
  }
  if (!(key & G15_KEY_G2) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G2) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G3) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G3) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(3);
  }
  if (!(key & G15_KEY_G3) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G3) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G4) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G4) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(4);
  }
  if (!(key & G15_KEY_G4) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G4) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G5) && !(key & G15_EXTENDED_KEY) 
            && !(key_state & G15_KEY_G5) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(5);
  }
  if (!(key & G15_KEY_G5) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G5) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G6) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G6) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(6);
  }
  if (!(key & G15_KEY_G6) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G6) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G7) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G7) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(7);
  }
  if (!(key & G15_KEY_G7) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G7) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G8) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G8) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(8);
  }
  if (!(key & G15_KEY_G8) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G8) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  if ((key & G15_KEY_G9) && !(key & G15_EXTENDED_KEY)
            && !(key_state & G15_KEY_G9) && !(key_state & G15_EXTENDED_KEY)) {
    run_gkey_cmd(9);
  }
  if (!(key & G15_KEY_G9) && !(key & G15_EXTENDED_KEY)
            && (key_state & G15_KEY_G9) && !(key_state & G15_EXTENDED_KEY)) {
    
  }
  
  /*
   * Handle Non-Extended G-Keys
   */
  
  if ((key & G15_KEY_G10) && !(key_state & G15_KEY_G10)) {
    run_gkey_cmd(10);
  }
  if (!(key & G15_KEY_G10) && (key_state & G15_KEY_G10)) {
    
  }
  if ((key & G15_KEY_G11) && !(key_state & G15_KEY_G11)) {
    run_gkey_cmd(11);
  }
  if (!(key & G15_KEY_G11) && (key_state & G15_KEY_G11)) {
    
  }
  if ((key & G15_KEY_G12) && !(key_state & G15_KEY_G12)) {
    run_gkey_cmd(12);
  }
  if (!(key & G15_KEY_G12) && (key_state & G15_KEY_G12)) {
    
  }
  if ((key & G15_KEY_G13) && !(key_state & G15_KEY_G13)) {
    run_gkey_cmd(13);
  }
  if (!(key & G15_KEY_G13) && (key_state & G15_KEY_G13)) {
    
  }
  if ((key & G15_KEY_G14) && !(key_state & G15_KEY_G14)) {
    run_gkey_cmd(14);
  }
  if (!(key & G15_KEY_G14) && (key_state & G15_KEY_G14)) {
    
  }
  if ((key & G15_KEY_G15) && !(key_state & G15_KEY_G15)) {
    run_gkey_cmd(15);
  }
  if (!(key & G15_KEY_G15) && (key_state & G15_KEY_G15)) {
    
  }
  if ((key & G15_KEY_G16) && !(key_state & G15_KEY_G16)) {
    run_gkey_cmd(16);
  }
  if (!(key & G15_KEY_G16) && (key_state & G15_KEY_G16)) {
    
  }
  if ((key & G15_KEY_G17) && !(key_state & G15_KEY_G17)) {
    run_gkey_cmd(17);
  }
  if (!(key & G15_KEY_G17) && (key_state & G15_KEY_G17)) {
    
  }
  if ((key & G15_KEY_G18) && !(key_state & G15_KEY_G18)) {
    run_gkey_cmd(18);
  }
  if (!(key & G15_KEY_G18) && (key_state & G15_KEY_G18)) {
    
  }
}