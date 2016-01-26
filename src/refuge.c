#include "refuge.h"

BaseWindow* current_window;
SplashWindow* splash_window;
MenuWindow* menu_window;

EventManager* event_manager;

static void push_window(BaseWindow* base_window) {
  window_stack_push(base_window_get_window(base_window), true);
  app_message_set_context(base_window_get_parent(base_window));
  app_message_register_inbox_received(base_window_get_inbox_handler(base_window));
  
  current_window = base_window;
}

//******************** Events ********************//
static void on_app_ready(void* context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "App Ready!");
}

static void on_washrooms_data(void* context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Washroom Data!!");
}

//******************** Application Setup ********************//

static void init(void) {
  event_manager = event_manager_create();
  event_manager_subscribe(event_manager, APP_READY_EVENT, on_app_ready);
  event_manager_subscribe(event_manager, WASHROOMS_DATA_EVENT, on_washrooms_data);
  
  app_message_open(INBOX_SIZE, OUTBOX_SIZE);

  splash_window = splash_window_create(event_manager, TXT_INITIALIZING, sizeof(TXT_INITIALIZING));
  push_window(splash_window_get_base(splash_window));
}

static void deinit(void) {
  event_manager_destroy(event_manager);

  if (splash_window) splash_window_destroy(splash_window);
  if (menu_window) menu_window_destroy(menu_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
