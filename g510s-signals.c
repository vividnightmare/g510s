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


#include <string.h>
#include <gtk/gtk.h>

#include "g510s.h"


extern GtkCheckMenuItem *menuhidden;

// menubar actions
void on_menusave_activate(GtkMenuItem *menuitem, gpointer window) {
  save_config();
}

void on_menuhidden_toggled(GtkMenuItem *menuitem, gpointer user_data) {
  if (gtk_check_menu_item_get_active(menuhidden) == TRUE) {
    g510s_data.gui_hidden = 1;
  } else {
    g510s_data.gui_hidden = 0;
  }
}

void on_menuabout_activate(GtkMenuItem *menuitem, gpointer aboutdialog) {
  gtk_widget_show(aboutdialog);
}

// scale actions
void on_red_adj_m1_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m1.red = gtk_range_get_value(scale);
  update = 1;
}

void on_green_adj_m1_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m1.green = gtk_range_get_value(scale);
  update = 1;
}

void on_blue_adj_m1_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m1.blue = gtk_range_get_value(scale);
  update = 1;
}

void on_red_adj_m2_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m2.red = gtk_range_get_value(scale);
  update = 2;
}

void on_green_adj_m2_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m2.green = gtk_range_get_value(scale);
  update = 2;
}

void on_blue_adj_m2_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m2.blue = gtk_range_get_value(scale);
  update = 2;
}

void on_red_adj_m3_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m3.red = gtk_range_get_value(scale);
  update = 3;
}

void on_green_adj_m3_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m3.green = gtk_range_get_value(scale);
  update = 3;
}

void on_blue_adj_m3_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.m3.blue = gtk_range_get_value(scale);
  update = 3;
}

void on_red_adj_mr_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.mr.red = gtk_range_get_value(scale);
  update = 4;
}

void on_green_adj_mr_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.mr.green = gtk_range_get_value(scale);
  update = 4;
}

void on_blue_adj_mr_value_changed(GtkAdjustment *adjustment, gpointer scale) {
  g510s_data.mr.blue = gtk_range_get_value(scale);
  update = 4;
}

// button actions
void on_closebutton_clicked(GtkButton *button, gpointer window) {
  gtk_widget_hide(window);
}

// indicator actions
void on_indicator_menushow_activate(GtkMenuItem *menuitem, gpointer window) {
  gtk_widget_show(window);
}

void on_indicator_menuhide_activate(GtkMenuItem *menuitem, gpointer window) {
  gtk_widget_hide(window);
}

void on_entry_m1g1_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g1, 0, sizeof(g510s_data.m1.g1));
  strncpy(g510s_data.m1.g1, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g1));
}

void on_entry_m1g2_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g2, 0, sizeof(g510s_data.m1.g2));
  strncpy(g510s_data.m1.g2, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g2));
}

void on_entry_m1g3_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g3, 0, sizeof(g510s_data.m1.g3));
  strncpy(g510s_data.m1.g3, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g3));
}

void on_entry_m1g4_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g4, 0, sizeof(g510s_data.m1.g4));
  strncpy(g510s_data.m1.g4, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g4));
}

void on_entry_m1g5_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g5, 0, sizeof(g510s_data.m1.g5));
  strncpy(g510s_data.m1.g5, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g5));
}

void on_entry_m1g6_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g6, 0, sizeof(g510s_data.m1.g6));
  strncpy(g510s_data.m1.g6, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g6));
}

void on_entry_m1g7_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g7, 0, sizeof(g510s_data.m1.g7));
  strncpy(g510s_data.m1.g7, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g7));
}

void on_entry_m1g8_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g8, 0, sizeof(g510s_data.m1.g8));
  strncpy(g510s_data.m1.g8, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g8));
}

void on_entry_m1g9_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g9, 0, sizeof(g510s_data.m1.g9));
  strncpy(g510s_data.m1.g9, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g9));
}

void on_entry_m1g10_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g10, 0, sizeof(g510s_data.m1.g10));
  strncpy(g510s_data.m1.g10, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g10));
}

void on_entry_m1g11_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g11, 0, sizeof(g510s_data.m1.g11));
  strncpy(g510s_data.m1.g11, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g11));
}

void on_entry_m1g12_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g12, 0, sizeof(g510s_data.m1.g12));
  strncpy(g510s_data.m1.g12, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g12));
}

void on_entry_m1g13_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g13, 0, sizeof(g510s_data.m1.g13));
  strncpy(g510s_data.m1.g13, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g13));
}

void on_entry_m1g14_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g14, 0, sizeof(g510s_data.m1.g14));
  strncpy(g510s_data.m1.g14, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g14));
}

void on_entry_m1g15_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g15, 0, sizeof(g510s_data.m1.g15));
  strncpy(g510s_data.m1.g15, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g15));
}

void on_entry_m1g16_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g16, 0, sizeof(g510s_data.m1.g16));
  strncpy(g510s_data.m1.g16, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g16));
}

void on_entry_m1g17_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g17, 0, sizeof(g510s_data.m1.g17));
  strncpy(g510s_data.m1.g17, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g17));
}

void on_entry_m1g18_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m1.g18, 0, sizeof(g510s_data.m1.g18));
  strncpy(g510s_data.m1.g18, gtk_entry_get_text(entry), sizeof(g510s_data.m1.g18));
}

void on_entry_m2g1_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g1, 0, sizeof(g510s_data.m2.g1));
  strncpy(g510s_data.m2.g1, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g1));
}

void on_entry_m2g2_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g2, 0, sizeof(g510s_data.m2.g2));
  strncpy(g510s_data.m2.g2, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g2));
}

void on_entry_m2g3_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g3, 0, sizeof(g510s_data.m2.g3));
  strncpy(g510s_data.m2.g3, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g3));
}

void on_entry_m2g4_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g4, 0, sizeof(g510s_data.m2.g4));
  strncpy(g510s_data.m2.g4, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g4));
}

void on_entry_m2g5_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g5, 0, sizeof(g510s_data.m2.g5));
  strncpy(g510s_data.m2.g5, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g5));
}

void on_entry_m2g6_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g6, 0, sizeof(g510s_data.m2.g6));
  strncpy(g510s_data.m2.g6, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g6));
}

void on_entry_m2g7_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g7, 0, sizeof(g510s_data.m2.g7));
  strncpy(g510s_data.m2.g7, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g7));
}

void on_entry_m2g8_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g8, 0, sizeof(g510s_data.m2.g8));
  strncpy(g510s_data.m2.g8, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g8));
}

void on_entry_m2g9_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g9, 0, sizeof(g510s_data.m2.g9));
  strncpy(g510s_data.m2.g9, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g9));
}

void on_entry_m2g10_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g10, 0, sizeof(g510s_data.m2.g10));
  strncpy(g510s_data.m2.g10, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g10));
}

void on_entry_m2g11_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g11, 0, sizeof(g510s_data.m2.g11));
  strncpy(g510s_data.m2.g11, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g11));
}

void on_entry_m2g12_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g12, 0, sizeof(g510s_data.m2.g12));
  strncpy(g510s_data.m2.g12, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g12));
}

void on_entry_m2g13_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g13, 0, sizeof(g510s_data.m2.g13));
  strncpy(g510s_data.m2.g13, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g13));
}

void on_entry_m2g14_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g14, 0, sizeof(g510s_data.m2.g14));
  strncpy(g510s_data.m2.g14, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g14));
}

void on_entry_m2g15_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g15, 0, sizeof(g510s_data.m2.g15));
  strncpy(g510s_data.m2.g15, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g15));
}

void on_entry_m2g16_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g16, 0, sizeof(g510s_data.m2.g16));
  strncpy(g510s_data.m2.g16, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g16));
}

void on_entry_m2g17_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g17, 0, sizeof(g510s_data.m2.g17));
  strncpy(g510s_data.m2.g17, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g17));
}

void on_entry_m2g18_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m2.g18, 0, sizeof(g510s_data.m2.g18));
  strncpy(g510s_data.m2.g18, gtk_entry_get_text(entry), sizeof(g510s_data.m2.g18));
}

void on_entry_m3g1_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g1, 0, sizeof(g510s_data.m3.g1));
  strncpy(g510s_data.m3.g1, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g1));
}

void on_entry_m3g2_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g2, 0, sizeof(g510s_data.m3.g2));
  strncpy(g510s_data.m3.g2, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g2));
}

void on_entry_m3g3_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g3, 0, sizeof(g510s_data.m3.g3));
  strncpy(g510s_data.m3.g3, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g3));
}

void on_entry_m3g4_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g4, 0, sizeof(g510s_data.m3.g4));
  strncpy(g510s_data.m3.g4, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g4));
}

void on_entry_m3g5_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g5, 0, sizeof(g510s_data.m3.g5));
  strncpy(g510s_data.m3.g5, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g5));
}

void on_entry_m3g6_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g6, 0, sizeof(g510s_data.m3.g6));
  strncpy(g510s_data.m3.g6, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g6));
}

void on_entry_m3g7_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g7, 0, sizeof(g510s_data.m3.g7));
  strncpy(g510s_data.m3.g7, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g7));
}

void on_entry_m3g8_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g8, 0, sizeof(g510s_data.m3.g8));
  strncpy(g510s_data.m3.g8, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g8));
}

void on_entry_m3g9_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g9, 0, sizeof(g510s_data.m3.g9));
  strncpy(g510s_data.m3.g9, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g9));
}

void on_entry_m3g10_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g10, 0, sizeof(g510s_data.m3.g10));
  strncpy(g510s_data.m3.g10, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g10));
}

void on_entry_m3g11_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g11, 0, sizeof(g510s_data.m3.g11));
  strncpy(g510s_data.m3.g11, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g11));
}

void on_entry_m3g12_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g12, 0, sizeof(g510s_data.m3.g12));
  strncpy(g510s_data.m3.g12, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g12));
}

void on_entry_m3g13_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g13, 0, sizeof(g510s_data.m3.g13));
  strncpy(g510s_data.m3.g13, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g13));
}

void on_entry_m3g14_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g14, 0, sizeof(g510s_data.m3.g14));
  strncpy(g510s_data.m3.g14, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g14));
}

void on_entry_m3g15_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g15, 0, sizeof(g510s_data.m3.g15));
  strncpy(g510s_data.m3.g15, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g15));
}

void on_entry_m3g16_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g16, 0, sizeof(g510s_data.m3.g16));
  strncpy(g510s_data.m3.g16, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g16));
}

void on_entry_m3g17_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g17, 0, sizeof(g510s_data.m3.g17));
  strncpy(g510s_data.m3.g17, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g17));
}

void on_entry_m3g18_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.m3.g18, 0, sizeof(g510s_data.m3.g18));
  strncpy(g510s_data.m3.g18, gtk_entry_get_text(entry), sizeof(g510s_data.m3.g18));
}

void on_entry_mrg1_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g1, 0, sizeof(g510s_data.mr.g1));
  strncpy(g510s_data.mr.g1, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g1));
}

void on_entry_mrg2_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g2, 0, sizeof(g510s_data.mr.g2));
  strncpy(g510s_data.mr.g2, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g2));
}

void on_entry_mrg3_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g3, 0, sizeof(g510s_data.mr.g3));
  strncpy(g510s_data.mr.g3, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g3));
}

void on_entry_mrg4_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g4, 0, sizeof(g510s_data.mr.g4));
  strncpy(g510s_data.mr.g4, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g4));
}

void on_entry_mrg5_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g5, 0, sizeof(g510s_data.mr.g5));
  strncpy(g510s_data.mr.g5, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g5));
}

void on_entry_mrg6_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g6, 0, sizeof(g510s_data.mr.g6));
  strncpy(g510s_data.mr.g6, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g6));
}

void on_entry_mrg7_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g7, 0, sizeof(g510s_data.mr.g7));
  strncpy(g510s_data.mr.g7, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g7));
}

void on_entry_mrg8_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g8, 0, sizeof(g510s_data.mr.g8));
  strncpy(g510s_data.mr.g8, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g8));
}

void on_entry_mrg9_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g9, 0, sizeof(g510s_data.mr.g9));
  strncpy(g510s_data.mr.g9, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g9));
}

void on_entry_mrg10_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g10, 0, sizeof(g510s_data.mr.g10));
  strncpy(g510s_data.mr.g10, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g10));
}

void on_entry_mrg11_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g11, 0, sizeof(g510s_data.mr.g11));
  strncpy(g510s_data.mr.g11, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g11));
}

void on_entry_mrg12_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g12, 0, sizeof(g510s_data.mr.g12));
  strncpy(g510s_data.mr.g12, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g12));
}

void on_entry_mrg13_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g13, 0, sizeof(g510s_data.mr.g13));
  strncpy(g510s_data.mr.g13, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g13));
}

void on_entry_mrg14_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g14, 0, sizeof(g510s_data.mr.g14));
  strncpy(g510s_data.mr.g14, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g14));
}

void on_entry_mrg15_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g15, 0, sizeof(g510s_data.mr.g15));
  strncpy(g510s_data.mr.g15, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g15));
}

void on_entry_mrg16_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g16, 0, sizeof(g510s_data.mr.g16));
  strncpy(g510s_data.mr.g16, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g16));
}

void on_entry_mrg17_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g17, 0, sizeof(g510s_data.mr.g17));
  strncpy(g510s_data.mr.g17, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g17));
}

void on_entry_mrg18_changed(GtkEntry *entry, gpointer user_data) {
  memset(g510s_data.mr.g18, 0, sizeof(g510s_data.mr.g18));
  strncpy(g510s_data.mr.g18, gtk_entry_get_text(entry), sizeof(g510s_data.mr.g18));
}