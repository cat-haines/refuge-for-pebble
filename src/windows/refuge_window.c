#include "refuge.h"

static RefugeWindow* this;

RefugeWindow* refuge_window_create(void* parent, AppMessageInboxReceived inbox_handler) {
  this = malloc(sizeof(RefugeWindow));
  
  this->window = window_create();
  this->inbox_handler = inbox_handler;
  this->parent = parent;

  return this;
}

void refuge_window_destroy(RefugeWindow* refuge_window) {
  if (!refuge_window) return;

  APP_LOG(APP_LOG_LEVEL_INFO, "Destroying RefugeWindow");

  if (refuge_window->window) window_destroy(refuge_window->window);
  if (refuge_window) free(refuge_window);

  // Set pointer to NULL (no dangling pointers for us)
  refuge_window = NULL;  
}

Window* refuge_window_get_window(RefugeWindow* refuge_window) {
  if (!refuge_window) return NULL;
  if (!refuge_window->window) return NULL;

  return refuge_window->window;
}

AppMessageInboxReceived refuge_window_get_inbox_handler(RefugeWindow* refuge_window) {
  if (!refuge_window) return NULL;
  return refuge_window->inbox_handler;
}

void* refuge_window_get_parent(RefugeWindow* refuge_window) {
 if (!refuge_window) return NULL;
  return refuge_window->parent; 
}