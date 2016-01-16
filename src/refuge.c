#include "refuge.h"

BaseWindow* current_window;

SplashWindow* splash_window;

static void push_window(BaseWindow* base_window) {
  window_stack_push(base_window_get_window(base_window), true);
  app_message_set_context(base_window_get_parent(base_window));
  app_message_register_inbox_received(base_window_get_inbox_handler(base_window));
  
  current_window = base_window;
}

static void init(void) {
  app_message_open(INBOX_SIZE, OUTBOX_SIZE);

  splash_window = splash_window_create(TXT_INITIALIZING, sizeof(TXT_INITIALIZING));
  push_window(splash_window_get_base(splash_window));
}

static void deinit(void) {
  if (splash_window) splash_window_destroy(splash_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
