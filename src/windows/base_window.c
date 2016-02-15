#include "refuge.h"

BaseWindow* base_window_create(void* parent, AppMessageInboxReceived inbox_handler, char name) {
  BaseWindow* this = malloc(sizeof(BaseWindow));

  this->window = window_create();
  this->inbox_handler = inbox_handler;
  this->parent = parent;
  this->name = name;

  return this;
}

void base_window_destroy(BaseWindow* this) {
  if (!this) return;

  if (this->window) window_destroy(this->window);
  if (this) free(this);

  // Set pointer to NULL (no dangling pointers for us)
  this = NULL;
}

Window* base_window_get_window(BaseWindow* this) {
  if (!this) return NULL;
  if (!this->window) return NULL;

  return this->window;
}

AppMessageInboxReceived base_window_get_inbox_handler(BaseWindow* this) {
  if (!this) return NULL;
  return this->inbox_handler;
}

void* base_window_get_parent(BaseWindow* this) {
 if (!this) return NULL;
  return this->parent;
}

char base_window_get_name(BaseWindow* this) {
  return this->name;
}