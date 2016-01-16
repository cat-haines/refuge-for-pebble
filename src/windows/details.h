#pragma once

#include "refuge.h"

typedef struct {
  RefugeWindow* base;
} DetailsWindow;

DetailsWindow* details_window_create();
void details_window_destroy(DetailsWindow* details_window);

RefugeWindow* details_window_get_base(DetailsWindow* details_window);