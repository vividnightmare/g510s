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
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "g510s.h"


void init_data() {
  // gui
  g510s_data.gui_hidden = 0;
  
  // function
  g510s_data.mkey_state = 1;
  
  // color
  g510s_data.m1.red = 255;
  g510s_data.m1.green = 255;
  g510s_data.m1.blue = 255;
  g510s_data.m2.red = 255;
  g510s_data.m2.green = 255;
  g510s_data.m2.blue = 255;
  g510s_data.m3.red = 255;
  g510s_data.m3.green = 255;
  g510s_data.m3.blue = 255;
  g510s_data.mr.red = 255;
  g510s_data.mr.green = 255;
  g510s_data.mr.blue = 255;
  
  // cmd strings
  memset(g510s_data.m1.g1, 0, sizeof(g510s_data.m1.g1));
  memset(g510s_data.m1.g2, 0, sizeof(g510s_data.m1.g2));
  memset(g510s_data.m1.g3, 0, sizeof(g510s_data.m1.g3));
  memset(g510s_data.m1.g4, 0, sizeof(g510s_data.m1.g4));
  memset(g510s_data.m1.g5, 0, sizeof(g510s_data.m1.g5));
  memset(g510s_data.m1.g6, 0, sizeof(g510s_data.m1.g6));
  memset(g510s_data.m1.g7, 0, sizeof(g510s_data.m1.g7));
  memset(g510s_data.m1.g8, 0, sizeof(g510s_data.m1.g8));
  memset(g510s_data.m1.g9, 0, sizeof(g510s_data.m1.g9));
  memset(g510s_data.m1.g10, 0, sizeof(g510s_data.m1.g10));
  memset(g510s_data.m1.g11, 0, sizeof(g510s_data.m1.g11));
  memset(g510s_data.m1.g12, 0, sizeof(g510s_data.m1.g12));
  memset(g510s_data.m1.g13, 0, sizeof(g510s_data.m1.g13));
  memset(g510s_data.m1.g14, 0, sizeof(g510s_data.m1.g14));
  memset(g510s_data.m1.g15, 0, sizeof(g510s_data.m1.g15));
  memset(g510s_data.m1.g16, 0, sizeof(g510s_data.m1.g16));
  memset(g510s_data.m1.g17, 0, sizeof(g510s_data.m1.g17));
  memset(g510s_data.m1.g18, 0, sizeof(g510s_data.m1.g18));
  
  memset(g510s_data.m2.g1, 0, sizeof(g510s_data.m2.g1));
  memset(g510s_data.m2.g2, 0, sizeof(g510s_data.m2.g2));
  memset(g510s_data.m2.g3, 0, sizeof(g510s_data.m2.g3));
  memset(g510s_data.m2.g4, 0, sizeof(g510s_data.m2.g4));
  memset(g510s_data.m2.g5, 0, sizeof(g510s_data.m2.g5));
  memset(g510s_data.m2.g6, 0, sizeof(g510s_data.m2.g6));
  memset(g510s_data.m2.g7, 0, sizeof(g510s_data.m2.g7));
  memset(g510s_data.m2.g8, 0, sizeof(g510s_data.m2.g8));
  memset(g510s_data.m2.g9, 0, sizeof(g510s_data.m2.g9));
  memset(g510s_data.m2.g10, 0, sizeof(g510s_data.m2.g10));
  memset(g510s_data.m2.g11, 0, sizeof(g510s_data.m2.g11));
  memset(g510s_data.m2.g12, 0, sizeof(g510s_data.m2.g12));
  memset(g510s_data.m2.g13, 0, sizeof(g510s_data.m2.g13));
  memset(g510s_data.m2.g14, 0, sizeof(g510s_data.m2.g14));
  memset(g510s_data.m2.g15, 0, sizeof(g510s_data.m2.g15));
  memset(g510s_data.m2.g16, 0, sizeof(g510s_data.m2.g16));
  memset(g510s_data.m2.g17, 0, sizeof(g510s_data.m2.g17));
  memset(g510s_data.m2.g18, 0, sizeof(g510s_data.m2.g18));
  
  memset(g510s_data.m3.g1, 0, sizeof(g510s_data.m3.g1));
  memset(g510s_data.m3.g2, 0, sizeof(g510s_data.m3.g2));
  memset(g510s_data.m3.g3, 0, sizeof(g510s_data.m3.g3));
  memset(g510s_data.m3.g4, 0, sizeof(g510s_data.m3.g4));
  memset(g510s_data.m3.g5, 0, sizeof(g510s_data.m3.g5));
  memset(g510s_data.m3.g6, 0, sizeof(g510s_data.m3.g6));
  memset(g510s_data.m3.g7, 0, sizeof(g510s_data.m3.g7));
  memset(g510s_data.m3.g8, 0, sizeof(g510s_data.m3.g8));
  memset(g510s_data.m3.g9, 0, sizeof(g510s_data.m3.g9));
  memset(g510s_data.m3.g10, 0, sizeof(g510s_data.m3.g10));
  memset(g510s_data.m3.g11, 0, sizeof(g510s_data.m3.g11));
  memset(g510s_data.m3.g12, 0, sizeof(g510s_data.m3.g12));
  memset(g510s_data.m3.g13, 0, sizeof(g510s_data.m3.g13));
  memset(g510s_data.m3.g14, 0, sizeof(g510s_data.m3.g14));
  memset(g510s_data.m3.g15, 0, sizeof(g510s_data.m3.g15));
  memset(g510s_data.m3.g16, 0, sizeof(g510s_data.m3.g16));
  memset(g510s_data.m3.g17, 0, sizeof(g510s_data.m3.g17));
  memset(g510s_data.m3.g18, 0, sizeof(g510s_data.m3.g18));
  
  memset(g510s_data.mr.g1, 0, sizeof(g510s_data.mr.g1));
  memset(g510s_data.mr.g2, 0, sizeof(g510s_data.mr.g2));
  memset(g510s_data.mr.g3, 0, sizeof(g510s_data.mr.g3));
  memset(g510s_data.mr.g4, 0, sizeof(g510s_data.mr.g4));
  memset(g510s_data.mr.g5, 0, sizeof(g510s_data.mr.g5));
  memset(g510s_data.mr.g6, 0, sizeof(g510s_data.mr.g6));
  memset(g510s_data.mr.g7, 0, sizeof(g510s_data.mr.g7));
  memset(g510s_data.mr.g8, 0, sizeof(g510s_data.mr.g8));
  memset(g510s_data.mr.g9, 0, sizeof(g510s_data.mr.g9));
  memset(g510s_data.mr.g10, 0, sizeof(g510s_data.mr.g10));
  memset(g510s_data.mr.g11, 0, sizeof(g510s_data.mr.g11));
  memset(g510s_data.mr.g12, 0, sizeof(g510s_data.mr.g12));
  memset(g510s_data.mr.g13, 0, sizeof(g510s_data.mr.g13));
  memset(g510s_data.mr.g14, 0, sizeof(g510s_data.mr.g14));
  memset(g510s_data.mr.g15, 0, sizeof(g510s_data.mr.g15));
  memset(g510s_data.mr.g16, 0, sizeof(g510s_data.mr.g16));
  memset(g510s_data.mr.g17, 0, sizeof(g510s_data.mr.g17));
  memset(g510s_data.mr.g18, 0, sizeof(g510s_data.mr.g18));
  
  // clock settings
  g510s_data.clock_mode = 0;
  g510s_data.show_date = 1;
}

int check_dir() {
  char home_path[255];
  char g510s_dir[] = "/.g510s";
  char *full_path;
  DIR *dir;
  
  strncpy(home_path, getenv("HOME"), sizeof(home_path));
  
  if (home_path == NULL) {
    printf("G510s: failed to find $HOME directory, using default settings\n");
    return -1;
  }
  
  full_path = malloc(sizeof(home_path) + sizeof(g510s_dir) + 1);
  strncpy(full_path, home_path, sizeof(home_path));
  strncat(full_path, g510s_dir, sizeof(g510s_dir));
  
  if ((dir = opendir(full_path)) == NULL) {
    if (mkdir(full_path, 0777) == -1) {
      printf("G510s: failed to create directory $HOME/.g510s\n");
      free(full_path);
      return -1;
    }
  }
  
  free(full_path);
  
  return 0;
}

int load_config() {
  char home_path[255];
  char file_name[] = "/.g510s/g510s.dat";
  char *full_path;
  FILE *file;
  
  strncpy(home_path, getenv("HOME"), sizeof(home_path));
  
  if (home_path == NULL) {
    printf("G510s: failed to find $HOME directory, using default settings\n");
    return -1;
  }
  
  full_path = malloc(sizeof(home_path) + sizeof(file_name) + 1);
  strncpy(full_path, home_path, sizeof(home_path));
  strncat(full_path, file_name, sizeof(file_name));
  
  if ((file = fopen(full_path, "rb")) == NULL) {
    printf("G510s: failed to read save file, using default settings\n");
    free(full_path);
    return -1;
  }
  
  fread(&g510s_data, sizeof(g510s_data), 1, file);
  fclose(file);
  
  free(full_path);
  
  return 0;
}

int save_config() {
  char home_path[255];
  char file_name[] = "/.g510s/g510s.dat";
  char *full_path;
  FILE *file;
  
  strncpy(home_path, getenv("HOME"), sizeof(home_path));
  
  if (home_path == NULL) {
    printf("G510s: failed to find $HOME directory, skipping save\n");
    return -1;
  }
  
  full_path = malloc(sizeof(home_path) + sizeof(file_name) + 1);
  strncpy(full_path, home_path, sizeof(home_path));
  strncat(full_path, file_name, sizeof(file_name));
  
  if ((file = fopen(full_path, "wb")) == NULL) {
    printf("G510s: failed to write save file\n");
    free(full_path);
    return -1;
  }
  
  fwrite(&g510s_data, sizeof(g510s_data), 1, file);
  fclose(file);
  
  free(full_path);
  
  return 0;
}