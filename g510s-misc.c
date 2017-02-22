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


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <libg15.h>

#include "g510s.h"


int is_number(char number[]) {
  int i = 0;
  if (number[0] == '-') {
    i = 1;
  }
  for (; number[i] != 0; i++) {
    if (!isdigit(number[i])) {
      return -1;
    }
  }
  return 0;
}

void setpixel(lcd_t *lcd, unsigned int x, unsigned int y, unsigned int val) {
  unsigned int curr_row = y;
  unsigned int curr_col = x;
  
  unsigned int pixel_offset = curr_row * G15_LCD_WIDTH + curr_col;
  unsigned int byte_offset = pixel_offset / 8;
  unsigned int bit_offset = 7 - (pixel_offset % 8);
  
  if (val) {
    lcd->buf[byte_offset] = lcd->buf[byte_offset] | 1 << bit_offset;
  } else {
    lcd->buf[byte_offset] = lcd->buf[byte_offset] & ~(1 << bit_offset);
  }
}

void convert_buf(lcd_t *lcd, unsigned char * orig_buf) {
  unsigned int x,y;
  for (x = 0; x < 160; x++) {
    for (y = 0; y < 43; y++) {
      setpixel(lcd, x, y, orig_buf[x+(y*160)]);
    }
  }
}

void set_mkey_state(int state) {
  switch (state) {
    case 1:
      g510s_data.mkey_state = state;
      update = g510s_data.mkey_state;
      setLEDs(G15_LED_M1 -0x20);
      break;
    case 2:
      g510s_data.mkey_state = state;
      update = g510s_data.mkey_state;
      setLEDs(G15_LED_M2 -0x20);
      break;
    case 3:
      g510s_data.mkey_state = state;
      update = g510s_data.mkey_state;
      setLEDs(G15_LED_M3 -0x20);
      break;
    case 4:
      g510s_data.mkey_state = state;
      update = g510s_data.mkey_state;
      setLEDs(G15_LED_MR -0x20);
      break;
    default:
      printf("G510s: invalid mkey!!\n");
      return;
  }
}

void set_color() {
  struct m_data_s *mkey;
  
  switch (g510s_data.mkey_state) {
    case 1:
      mkey = &g510s_data.m1;
      break;
    case 2:
      mkey = &g510s_data.m2;
      break;
    case 3:
      mkey = &g510s_data.m3;
      break;
    case 4:
      mkey = &g510s_data.mr;
      break;
    default:
      printf("G510s: invalide mkey!!\n");
      return;
  }
  
  setG510LEDColor(mkey->red, mkey->green, mkey->blue);
}

void run_gkey_cmd(int gkey) {
  char *cmd;
  struct m_data_s *mkey;
  
  switch (g510s_data.mkey_state) {
    case 1:
      mkey = &g510s_data.m1;
      break;
    case 2:
      mkey = &g510s_data.m2;
      break;
    case 3:
      mkey = &g510s_data.m3;
      break;
    case 4:
      mkey = &g510s_data.mr;
      break;
    default:
      printf("G510s: invalid mkey!!\n");
      return;
  }
  
  switch (gkey) {
    case 1:
      cmd = mkey->g1;
      break;
    case 2:
      cmd = mkey->g2;
      break;
    case 3:
      cmd = mkey->g3;
      break;
    case 4:
      cmd = mkey->g4;
      break;
    case 5:
      cmd = mkey->g5;
      break;
    case 6:
      cmd = mkey->g6;
      break;
    case 7:
      cmd = mkey->g7;
      break;
    case 8:
      cmd = mkey->g8;
      break;
    case 9:
      cmd = mkey->g9;
      break;
    case 10:
      cmd = mkey->g10;
      break;
    case 11:
      cmd = mkey->g11;
      break;
    case 12:
      cmd = mkey->g12;
      break;
    case 13:
      cmd = mkey->g13;
      break;
    case 14:
      cmd = mkey->g14;
      break;
    case 15:
      cmd = mkey->g15;
      break;
    case 16:
      cmd = mkey->g16;
      break;
    case 17:
      cmd = mkey->g17;
      break;
    case 18:
      cmd = mkey->g18;
      break;
    default:
      printf("G510s: invalid gkey!!\n");
      return;
  }
  
  system(cmd);
}