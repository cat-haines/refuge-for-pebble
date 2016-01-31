#pragma once

#include "refuge.h"

typedef struct {
  BaseWindow* base;

  EventManager* event_manager;
} DetailsWindow;

DetailsWindow* details_window_create();
void details_window_destroy(DetailsWindow* details_window);

BaseWindow* details_window_get_base(DetailsWindow* details_window);