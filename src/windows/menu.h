#pragma once

#include "refuge.h"
#include "menu.h"

#define NUM_SECTIONS 1

typedef struct {
  BaseWindow* base;

  EventManager* event_manager;
} MenuWindow;

MenuWindow* menu_window_create(EventManager* event_manager);
void menu_window_destroy(MenuWindow* menu_window);

BaseWindow* menu_window_get_base(MenuWindow* menu_window);