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
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "g510s.h"


void send_keystate(lcd_t *client, unsigned int key) {
  int sock = client->connection;
  int msgret;
  
  if ((msgret = send(sock, (void *)&key, sizeof(key), 0)) < 0) {
    printf("G510s: socket send failed\n");
  }
}

int client_connect(lcdlist_t **lcdlist, int listening_socket) {
  int conn_s;
  struct pollfd pfd[1];
  pthread_t client_connection;
  pthread_attr_t attr;
  lcdnode_t *clientnode;
  
  memset(pfd, 0, sizeof(pfd));
  pfd[0].fd = listening_socket;
  pfd[0].events = POLLIN;
  
  if (poll(pfd, 1, 500) > 0) {
    if (!(pfd[0].revents & POLLIN)) {
      return 0;
    }
    
    if ((conn_s = accept(listening_socket, NULL, NULL)) < 0) {
      if (errno == EWOULDBLOCK || errno == EAGAIN) {
        // nothing
      } else {
        printf("G510s: error calling accept\n");
        return -1;
      }
    }
    
    clientnode = lcdnode_add(lcdlist);
    clientnode->lcd->connection = conn_s;
    
    memset(&attr, 0, sizeof(pthread_attr_t));
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setstacksize(&attr, 256*1024);
    if (pthread_create(&client_connection, &attr, lcd_client_function, clientnode) != 0) {
      printf("G510s: unable to create client thread\n");
      if (close(conn_s) < 0) {
        printf("G510s: error calling close\n");
        return -1;
      }
    }
    
    pthread_detach(client_connection);
  }
  return 0;
}

static void process_client_cmds(lcdnode_t *lcdnode, int sock, unsigned int *msgbuf, unsigned int len) {
  int msgret;
  
  if (msgbuf[0] == CLIENT_CMD_GET_KEYSTATE) {
    if (lcdnode->list->current == lcdnode) {
      if ((msgret = send(sock, (void *)&current_key_state, sizeof(current_key_state), 0)) < 0) {
        printf("G510s: socket send failed\n");
      }
      current_key_state = 0;
    } else {
      memset(msgbuf, 0, 4);
      msgret = send(sock, (void *)msgbuf, sizeof(current_key_state), 0);
    }
  } else if (msgbuf[0] == CLIENT_CMD_SWITCH_PRIORITIES) {
    //pthread_mutex_lock(&lcdlist_mutex);
    if (lcdnode->list->current != lcdnode) {
      lcdnode->last_priority = lcdnode->list->current;
      lcdnode->list->current = lcdnode;
    } else {
      if (lcdnode->list->current == lcdnode->last_priority) {
        lcdnode->list->current = lcdnode->list->current->prev;
      } else {
        if (lcdnode->last_priority != NULL) {
          lcdnode->list->current = lcdnode->last_priority;
          lcdnode->last_priority = NULL;
        } else {
          lcdnode->list->current = lcdnode->list->current->prev;
        }
      }
    }
    //pthread_mutex_unlock(&lcdlist_mutex);
  } else if (msgbuf[0] == CLIENT_CMD_IS_FOREGROUND) {
    //pthread_mutex_lock(&lcdlist_mutex);
    if (lcdnode->list->current == lcdnode) {
      msgbuf[0] = '1';
    } else {
      msgbuf[0] = '0';
    }
    //pthread_mutex_unlock(&lcdlist_mutex);
    send(sock, msgbuf, 1, 0);
  } else if (msgbuf[0] == CLIENT_CMD_IS_USER_SELECTED) {
    //pthread_mutex_lock(&lcdlist_mutex);
    if (lcdnode->lcd->usr_foreground) {
      msgbuf[0] = '1';
    } else {
      msgbuf[0] = '0';
    }
    //pthread_mutex_unlock(&lcdlist_mutex);
    send(sock, msgbuf, 1, 0);
  } else if (msgbuf[0] & CLIENT_CMD_BACKLIGHT) {
    // nothing
  } else if (msgbuf[0] & CLIENT_CMD_KEY_HANDLER) {
    // nothing
  }
}

int init_sockserver() {
  int listening_socket;
  int yes = 1;
  int tos = 0x18;
  
  struct sockaddr_in servaddr;
  
  if ((listening_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("G510s: unable to create socket\n");
    return -1;
  }
  
  setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  setsockopt(listening_socket, SOL_SOCKET, SO_PRIORITY, &tos, sizeof(tos));
  
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  inet_aton(LISTEN_ADDR, &servaddr.sin_addr);
  servaddr.sin_port = htons(LISTEN_PORT);
  
  if (bind(listening_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    printf("G510s: error calling bind\n");
    return -1;
  }
  
  if (listen(listening_socket, MAX_CLIENTS) < 0) {
    printf("G510s: error calling listen\n");
    return -1;
  }
  
  return listening_socket;
}

int g15_send(int sock, char *buf, unsigned int len) {
  int total = 0;
  int retval = 0;
  int bytesleft = len;
  struct pollfd pfd[1];
  
  while (total < len && leaving == 0) {
    memset(pfd, 0, sizeof(pfd));
    pfd[0].fd = sock;
    pfd[0].events = POLLOUT | POLLERR | POLLHUP | POLLNVAL;
    
    if (poll(pfd, 1, 500) > 0) {
      if (pfd[0].revents & POLLOUT && !(pfd[0].revents & POLLERR || pfd[0].revents & POLLHUP || pfd[0].revents & POLLNVAL)) {
        retval = send(sock, buf+total, bytesleft, 0);
        if (retval == -1) {
          break;
        }
        bytesleft -= retval;
        total += retval;
      }
      if (pfd[0].revents & POLLERR || pfd[0].revents & POLLHUP || pfd[0].revents & POLLNVAL) {
        retval = -1;
        break;
      }
    }
  }
  return retval == -1 ? -1 : 0;
}

int g15_recv(lcdnode_t *lcdnode, int sock, char *buf, unsigned int len) {
  int total = 0;
  int retval = 0;
  int msgret = 0;
  int bytesleft = len;
  struct pollfd pfd[1];
  unsigned int msgbuf[20];
  
  while (total < len && leaving == 0) {
    memset(pfd, 0, sizeof(pfd));
    pfd[0].fd = sock;
    pfd[0].events = POLLIN | POLLPRI | POLLERR | POLLHUP | POLLNVAL;
    
    if (poll(pfd, 1, 500) > 0) {
      if (pfd[0].revents & POLLPRI && !(pfd[0].revents & POLLERR || pfd[0].revents & POLLHUP || pfd[0].revents & POLLNVAL)) {
        memset(msgbuf, 0, 20);
        msgret = recv(sock, msgbuf, 10, MSG_OOB);
        if (msgret < 1) {
          break;
        }
        process_client_cmds(lcdnode, sock, msgbuf, len);
      } else if (pfd[0].revents & POLLIN && !(pfd[0].revents & POLLERR || pfd[0].revents & POLLHUP || pfd[0].revents & POLLNVAL)) {
        retval = recv(sock, buf+total, bytesleft, 0);
        if (retval < 1) {
          break;
        }
        total += retval;
        bytesleft -= retval;
      }
      if ((pfd[0].revents & POLLERR || pfd[0].revents & POLLHUP || pfd[0].revents & POLLNVAL)) {
        retval = -1;
        break;
      }
    }
  }
  return total;
}