#pragma once

#include "refuge.h"

typedef struct {
  RefugeWindow* base;
} MenuWindow;

MenuWindow* menu_window_create();
void menu_window_destroy(MenuWindow* menu_window);

RefugeWindow* menu_window_get_base(MenuWindow* menu_window);