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
#include <time.h>
#include <pthread.h>
#include <libg15.h>
#include <libg15render.h>

#include "g510s.h"


void digital_clock(lcd_t *lcd) {
  time_t currtime = time(NULL);
  
  if ((lcd->ident / 60) != (currtime / 60)) {
    g15canvas *canvas = (g15canvas *)malloc(sizeof(g15canvas));
    
    if (canvas == NULL) {
      printf("G510s: failed to create clock canvas\n");
      return;
    }
    
    char hour_buf[3];
    char min_buf[3];
    memset(hour_buf, 0, 3);
    memset(min_buf, 0, 3);
    
    memset(canvas->buffer, 0, G15_BUFFER_LEN);
    canvas->mode_cache = 0;
    canvas->mode_reverse = 0;
    canvas->mode_xor = 0;
    
    // 12 hour format
    if (!g510s_data.clock_mode) {
      char ampm_buf[3];
      memset(ampm_buf, 0, 3);
      strftime(hour_buf, 3, "%l", localtime(&currtime));
      strftime(ampm_buf, 3, "%p", localtime(&currtime));
      g15r_renderString(canvas, (unsigned char *)ampm_buf, 0, G15_TEXT_LARGE, 135, 26);
    } else { // 24 hour format
      strftime(hour_buf, 3, "%H", localtime(&currtime));
    }
    g15r_renderString(canvas, (unsigned char *)hour_buf, 0, 39, 30, 2);
    
    g15r_G15FPrint(canvas, ":", 77, -3, 39, 0, 1, 0);
    
    // minute
    strftime(min_buf, 3, "%M", localtime(&currtime));
    g15r_renderString(canvas, (unsigned char *)min_buf, 0, 39, 86, 2);
    
    // date string
    if (g510s_data.show_date) {
      char date_buf[40];
      memset(date_buf, 0, 40);
      strftime(date_buf, 40, "%A %B %e %Y", localtime(&currtime));
      g15r_renderString(canvas, (unsigned char *)date_buf, 0, G15_TEXT_MED, 80 - ((strlen(date_buf) * 5) / 2), 35);
    }
    
    //pthread_mutex_lock(&lcdlist_mutex);
    memset(lcd->buf, 0, G15_BUFFER_LEN);
    memcpy(lcd->buf, canvas->buffer, G15_BUFFER_LEN);
    lcd->ident = currtime;
    //pthread_mutex_unlock(&lcdlist_mutex);
    
    free(canvas);
  }
  return;
}