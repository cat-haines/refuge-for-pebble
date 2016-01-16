#pragma once

#include "refuge.h"

typedef struct {
  Window* window;
  AppMessageInboxReceived inbox_handler;
  void* parent;
} BaseWindow; 

BaseWindow* base_window_create(void* parent, AppMessageInboxReceived inbox_handler);
void base_window_destroy(BaseWindow* base_window);

Window* base_window_get_window(BaseWindow* base_window);
AppMessageInboxReceived base_window_get_inbox_handler(BaseWindow* windobase_window);
void* base_window_get_parent(BaseWindow* base_window);