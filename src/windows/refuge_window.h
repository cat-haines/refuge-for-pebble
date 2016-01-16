#pragma once

#include "refuge.h"

typedef struct {
  Window* window;
  AppMessageInboxReceived inbox_handler;
  void* parent;
} RefugeWindow; 

RefugeWindow* refuge_window_create(void* parent, AppMessageInboxReceived inbox_handler);
void refuge_window_destroy(RefugeWindow* refuge_window);

Window* refuge_window_get_window(RefugeWindow* refuge_window);
AppMessageInboxReceived refuge_window_get_inbox_handler(RefugeWindow* windorefuge_window);
void* refuge_window_get_parent(RefugeWindow* refuge_window);