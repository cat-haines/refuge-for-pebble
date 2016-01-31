#include "refuge.h"
#include "menu.h"


static void inbox_handler(DictionaryIterator* iter, void* context) {
  // SplashWindow* this = base_window_get_parent(context);
}

static void window_load(Window* window) {
  // SplashWindow* this = base_window_get_parent(window_get_user_data(window));

  // Layer* window_layer = window_get_root_layer(window);
  // GRect bounds = layer_get_bounds(window_layer);
}

static void window_unload(Window* window) {

}

MenuWindow* menu_window_create(EventManager* event_manager) {
  MenuWindow* this = malloc(sizeof(MenuWindow));
  this->base = base_window_create(this, (AppMessageInboxReceived) inbox_handler);
  this->event_manager = event_manager;

  Window* window = base_window_get_window(this->base);
  window_set_user_data(window, this->base);

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });

  return this;
}

void menu_window_destroy(MenuWindow* this) {

}

BaseWindow* menu_window_get_base(MenuWindow* this) {
  return this->base;
}