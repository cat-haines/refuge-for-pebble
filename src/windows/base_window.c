#include "refuge.h"

static BaseWindow* this;

BaseWindow* base_window_create(void* parent, AppMessageInboxReceived inbox_handler) {
  this = malloc(sizeof(BaseWindow));
  
  this->window = window_create();
  this->inbox_handler = inbox_handler;
  this->parent = parent;

  return this;
}

void base_window_destroy(BaseWindow* base_window) {
  if (!base_window) return;

  APP_LOG(APP_LOG_LEVEL_INFO, "Destroying BaseWindow");

  if (base_window->window) window_destroy(base_window->window);
  if (base_window) free(base_window);

  // Set pointer to NULL (no dangling pointers for us)
  base_window = NULL;  
}

Window* base_window_get_window(BaseWindow* base_window) {
  if (!base_window) return NULL;
  if (!base_window->window) return NULL;

  return base_window->window;
}

AppMessageInboxReceived base_window_get_inbox_handler(BaseWindow* base_window) {
  if (!base_window) return NULL;
  return base_window->inbox_handler;
}

void* base_window_get_parent(BaseWindow* base_window) {
 if (!base_window) return NULL;
  return base_window->parent; 
}