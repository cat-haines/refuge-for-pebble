#pragma once

#include "refuge.h"

typedef struct {
  BaseWindow* base;
} MenuWindow;

MenuWindow* menu_window_create();
void menu_window_destroy(MenuWindow* menu_window);

BaseWindow* menu_window_get_base(MenuWindow* menu_window);