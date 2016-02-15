#pragma once

#include "refuge.h"

typedef struct {
  Window* window;
  AppMessageInboxReceived inbox_handler;
  void* parent;
  char name;
} BaseWindow;

BaseWindow* base_window_create(void* parent, AppMessageInboxReceived inbox_handler, char name);
void base_window_destroy(BaseWindow* base_window);

Window* base_window_get_window(BaseWindow* base_window);
AppMessageInboxReceived base_window_get_inbox_handler(BaseWindow* base_window);
void* base_window_get_parent(BaseWindow* base_window);

char base_window_get_name(BaseWindow* base_window);