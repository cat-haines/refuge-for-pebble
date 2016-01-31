#pragma once

#include "refuge.h"
#include "menu.h"

typedef struct {
  BaseWindow* base;
  MenuLayer* menu_layer;

  uint16_t num_rows;

  EventManager* event_manager;
} MenuWindow;

MenuWindow* menu_window_create(EventManager* event_manager);
void menu_window_destroy(MenuWindow* menu_window);

BaseWindow* menu_window_get_base(MenuWindow* menu_window);