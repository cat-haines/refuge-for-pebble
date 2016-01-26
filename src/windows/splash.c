#include "refuge.h"
#include "splash.h"

static SplashWindow* this;

static void splash_window_inbox_handler(DictionaryIterator* iter, void* context) {
  Tuple *reply_tuple = dict_find(iter, MSG_APP_READY);

  if (reply_tuple) {
    // App Ready Event
    SplashWindow* window = (SplashWindow*) context;
    
    // Cancel the timeout timer if it's set
    if (window->timeout_timer) {
      app_timer_cancel(window->timeout_timer);
      window->timeout_timer = NULL;
    }
    splash_window_set_message(window, TXT_CONNECTED, sizeof(TXT_CONNECTED));
    event_manager_raise_event(this->event_manager, APP_READY_EVENT);

  } else if ((reply_tuple = dict_find(iter, MSG_WASHROOMS))) {
    // Washrooms Data Event
    event_manager_raise_event(this->event_manager, WASHROOMS_DATA_EVENT);
  }
}

static void splash_window_on_timeout(void* data) {
  splash_window_set_message((SplashWindow*) data, TXT_NO_CONNECTION, sizeof(TXT_NO_CONNECTION));
}

static void splash_window_load(Window* window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Loading SplashWindow->Window");

  Layer* window_layer = window_get_root_layer(window);
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
  layer_add_child(window_layer, text_layer_get_layer(this->message_layer));

  this->timeout_timer = app_timer_register(SPLASH_TIMEOUT, splash_window_on_timeout, this);
}

static void splash_window_unload(Window* window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Unloading SplashWindow->window");
  
  // Clean up all teh layers and layer information
  text_layer_destroy(this->message_layer); this->message_layer = NULL;
  gbitmap_destroy(this->bitmap); this->bitmap = NULL;
  bitmap_layer_destroy(this->bitmap_layer); this->bitmap_layer = NULL;

  if (this->timeout_timer) { app_timer_cancel(this->timeout_timer); this->timeout_timer = NULL; }
}

SplashWindow* splash_window_create(EventManager* event_manager, char* init_message, int n) {
  this = malloc(sizeof(SplashWindow));  
  this->base = base_window_create(this, (AppMessageInboxReceived) splash_window_inbox_handler);
  this->event_manager = event_manager;

  window_set_window_handlers(base_window_get_window(this->base), (WindowHandlers) {
    .load = splash_window_load,
    .unload = splash_window_unload
  });

  splash_window_set_message(this, init_message, n);
  
  return this;
}

void splash_window_destroy(SplashWindow* splash) {
  if (!splash) return;

  APP_LOG(APP_LOG_LEVEL_INFO, "Destroying SplashWindow");

  // Clean everything up
  if (splash->message_layer) text_layer_destroy(splash->message_layer);
  if (splash->bitmap) gbitmap_destroy(splash->bitmap);
  if (splash->bitmap_layer) bitmap_layer_destroy(splash->bitmap_layer);
  if (splash->base) base_window_destroy(splash->base);
  if (splash->timeout_timer) app_timer_cancel(splash->timeout_timer);
  if (splash) free(splash);

  // Set pointer to NULL (no dangling pointers for us)
  splash = NULL;
}

void splash_window_set_message(SplashWindow* splash, char* message, int n) {
  if (!splash) return;

  APP_LOG(APP_LOG_LEVEL_INFO, "SETTING MESSAGE");

  if (n > 32) n = 32;
  
  strncpy(splash->message_text, message, n);
  APP_LOG(APP_LOG_LEVEL_INFO, splash->message_text);

  if(splash->message_layer) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Redrawing SplashWindow->message_layer");
    text_layer_set_text(splash->message_layer, splash->message_text);
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "No Layer :(");
  }
}

void splash_window_clear_message(SplashWindow* splash) {
  if (!splash) return;

  splash_window_set_message(splash, "", 0);
}

BaseWindow* splash_window_get_base(SplashWindow* splash) {
  if (!splash) return NULL;

  return splash->base;
}

