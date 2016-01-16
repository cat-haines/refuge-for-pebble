#include "refuge.h"

RefugeWindow* current_window;

SplashWindow* splash_window;

static void push_window(RefugeWindow* refuge_window) {
  window_stack_push(refuge_window_get_window(refuge_window), true);
  app_message_set_context(refuge_window_get_parent(refuge_window));
  app_message_register_inbox_received(refuge_window_get_inbox_handler(refuge_window));
  
  current_window = refuge_window;
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
