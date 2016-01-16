#include "windows/splash.h"

static void splash_window_load(Window* window) {
  SplashWindow* this = window_get_user_data(window);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  this->bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH);
  
  this->bitmap_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(this->bitmap_layer, this->bitmap);
  bitmap_layer_set_compositing_mode(this->bitmap_layer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(this->bitmap_layer));

  this->message_layer = text_layer_create((GRect) {
    .size = { bounds.size.w, 20 },
    .origin = { 0, bounds.size.h / 2 + 30 }
  });

  text_layer_set_background_color(this->message_layer, GColorClear);
  text_layer_set_text_color(this->message_layer, GColorWhite);
  text_layer_set_text_alignment(this->message_layer, GTextAlignmentCenter);
  
  text_layer_set_text(this->message_layer, this->message_text);

  layer_add_child(bitmap_layer_get_layer(this->bitmap_layer), 
                  text_layer_get_layer(this->message_layer));
}

static void splash_window_unload(Window* window) {
  SplashWindow* this = window_get_user_data(window);

  // Clean up all teh layers and layer information
  text_layer_destroy(this->message_layer); this->message_layer = NULL;
  gbitmap_destroy(this->bitmap); this->bitmap = NULL;
  bitmap_layer_destroy(this->bitmap_layer); this->bitmap_layer = NULL;
}

SplashWindow* splash_window_create(char* init_message, int n) {
  SplashWindow* this = malloc(sizeof(SplashWindow));
  this->window = window_create();

  window_set_user_data(this->window, this);

  // Set initial value
  splash_window_set_message(this, init_message, n);

  window_set_window_handlers(this->window, (WindowHandlers) {
    .load = splash_window_load,
    .unload = splash_window_unload
  });

  return this;
}

void splash_window_set_message(SplashWindow* splash, char* message, int n) {
  if (!splash) return;

  if (n > 32) n = 32;
  strncpy(splash->message_text, message, n);
}

void splash_window_clear_message(SplashWindow* splash) {
  if (!splash) return;

  splash_window_set_message(splash, "", 0);
}

Window* splash_window_get_window(SplashWindow* splash) {
  if (!splash) return NULL;

  return splash->window;
}

void splash_window_destroy(SplashWindow* splash) {
  if (!splash) return;

  // Clean everything up
  if (splash->message_layer) text_layer_destroy(splash->message_layer);
  if (splash->bitmap) gbitmap_destroy(splash->bitmap);
  if (splash->bitmap_layer) bitmap_layer_destroy(splash->bitmap_layer);
  if (splash->window) window_destroy(splash->window);
  if (splash) free(splash);

  // Set pointer to NULL (no dangling pointers for us)
  splash = NULL;
}
