#pragma once

#include "refuge.h"
#include "menu.h"

typedef struct {
  int distance;
  char* name;
  char* subtitle;
} MenuItem;

MenuItem* menu_item_create(int distance, char* name, int name_len);
void menu_item_destroy(MenuItem* item);

typedef struct {
  BaseWindow* base;
  MenuLayer* menu_layer;

  EventManager* event_manager;

  uint16_t num_rows;
  MenuItem** items;
} MenuWindow;

MenuWindow* menu_window_create(EventManager* event_manager);
void menu_window_destroy(MenuWindow* menu_window);

BaseWindow* menu_window_get_base(MenuWindow* menu_window);