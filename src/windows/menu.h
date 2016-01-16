#pragma once

#include "refuge.h"

typedef struct {
  Window* window;
} MenuWindow;

MenuWindow* menu_window_create();
void menu_window_destroy();
