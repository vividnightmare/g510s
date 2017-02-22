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


#include <stdlib.h>
#include <pthread.h>
#include <libg15.h>

#include "g510s.h"


lcd_t * create_lcd() {
  lcd_t *lcd = malloc(sizeof(lcd_t));
  lcd->max_x = G15_LCD_WIDTH;
  lcd->max_y = G15_LCD_HEIGHT;
  lcd->backlight_state = G15_BRIGHTNESS_MEDIUM;
  lcd->mkey_state = G15_LED_MR;
  lcd->contrast_state = G15_CONTRAST_MEDIUM;
  lcd->state_changed = 1;
  lcd->usr_foreground = 0;
  
  return (lcd);
}

void quit_lcd(lcd_t * lcd) {
  free(lcd);
}

lcdlist_t *lcdlist_init() {
  lcdlist_t *displaylist = NULL;
  
  //pthread_mutex_init(&lcdlist_mutex, NULL);
  //pthread_mutex_lock(&lcdlist_mutex);
  
  displaylist = malloc(sizeof(lcdnode_t));
  
  displaylist->head = malloc(sizeof(lcdnode_t));
  
  displaylist->tail = displaylist->head;
  displaylist->current = displaylist->head;
  
  displaylist->head->lcd = create_lcd();
  displaylist->head->lcd->mkey_state = 0;
  
  displaylist->head->prev = displaylist->head;
  displaylist->head->next = displaylist->head;
  displaylist->head->list = displaylist;
  
  //pthread_mutex_unlock(&lcdlist_mutex);
  
  return displaylist;
}

lcdnode_t *lcdnode_add(lcdlist_t **display_list) {
  lcdnode_t *new = NULL;
  
  //pthread_mutex_lock(&lcdlist_mutex);
  
  new = malloc(sizeof(lcdnode_t));
  new->prev = (*display_list)->head;
  new->next = (*display_list)->tail;
  new->lcd = create_lcd();
  new->last_priority = NULL;
  
  (*display_list)->head->next = new;
  (*display_list)->current = new;
  
  (*display_list)->head = new;
  (*display_list)->head->list = *display_list;
  
  //pthread_mutex_unlock(&lcdlist_mutex);
  
  return new;
}

void lcdnode_remove(lcdnode_t *oldnode) {
  lcdlist_t **display_list = NULL;
  lcdnode_t **prev = NULL;
  lcdnode_t **next = NULL;
  
  //pthread_mutex_lock(&lcdlist_mutex);
  
  display_list = &oldnode->list;
  prev = &oldnode->prev;
  next = &oldnode->next;
  
  quit_lcd(oldnode->lcd);
  
  if ((*display_list)->current == oldnode) {
    if ((*display_list)->current != (*display_list)->head) {
      (*display_list)->current = oldnode->next;
    } else {
      (*display_list)->current = oldnode->prev;
    }
    (*display_list)->current->lcd->state_changed = 1;
  }
  
  if ((*display_list)->head != oldnode) {
    (*next)->prev = oldnode->prev;
    (*prev)->next = oldnode->next;
  } else {
    (*prev)->next = (*display_list)->tail;
    (*display_list)->head = oldnode->prev;
  }
  
  free(oldnode);
  
  //pthread_mutex_unlock(&lcdlist_mutex);
}

void lcdlist_destroy(lcdlist_t **displaylist) {
  int i = 0;
  
  while ((*displaylist)->head != (*displaylist)->tail) {
    i++;
    lcdnode_remove((*displaylist)->head);
  }
  
  free((*displaylist)->tail->lcd);
  free((*displaylist)->tail);
  free(*displaylist);
  
  //pthread_mutex_destroy(&lcdlist_mutex);
}