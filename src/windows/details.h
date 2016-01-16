#pragma once

#include "refuge.h"

typedef struct {
  Window* window;
} DetailsWindow;

DetailsWindow* details_window_create();
void details_window_destroy();
