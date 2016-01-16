#include "refuge.h"

static SplashWindow *splash_window;
// static MenuWindow *menu_window;
// static DetailsWindow *details_window;

static void* current_window;

static void init(void) {
  splash_window = splash_window_create(INITIALIZING, sizeof(INITIALIZING));

  window_stack_push(splash_window_get_window(splash_window), true);
  current_window = splash_window;

}

static void deinit(void) {
  splash_window_destroy(splash_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
