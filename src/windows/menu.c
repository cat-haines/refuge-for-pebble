#include "refuge.h"
#include "menu.h"

static void inbox_handler(DictionaryIterator* iter, void* context) {
  // SplashWindow* this = base_window_get_parent(context);
}

static uint16_t menu_get_num_rows(MenuLayer *menu_layer, uint16_t section_index, void* context) {
  MenuWindow* this = context;
  return this->num_rows;
}

static void menu_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *this) {
  menu_cell_basic_draw(ctx, cell_layer, "Basic Item", "With a subtitle", NULL);
}

static void on_down_click(ClickRecognizerRef recognizer, void* context) {
  MenuWindow* this = context;
  menu_layer_set_selected_next(this->menu_layer, false, MenuRowAlignCenter, false);
}

static void on_up_click(ClickRecognizerRef recognizer, void* context) {
  MenuWindow* this = context;
  menu_layer_set_selected_next(this->menu_layer, true, MenuRowAlignCenter, false);
}

static void on_back_click(ClickRecognizerRef recognizer, void* context) {
  MenuWindow* this = context;
  event_manager_raise_event_with_context(this->event_manager, MENU_BACK_EVENT, this->base);
}

static void on_select_click(ClickRecognizerRef recognizer, void* context) {
  const MenuWindow* this = context;
  MenuIndex index = menu_layer_get_selected_index(this->menu_layer);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", index.row);
}

static void click_config_provider(void* context) {
  window_single_click_subscribe(BUTTON_ID_UP, on_up_click);
  window_single_click_subscribe(BUTTON_ID_DOWN, on_down_click);
  window_single_click_subscribe(BUTTON_ID_BACK, on_back_click);
  window_single_click_subscribe(BUTTON_ID_SELECT, on_select_click);
}


static void window_load(Window* window) {  
  MenuWindow* this = base_window_get_parent(window_get_user_data(window));
  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create and configure the menu layer
  this->menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(this->menu_layer, this, (MenuLayerCallbacks){
    .get_num_rows = menu_get_num_rows,
    .draw_row = menu_draw_row,
  });

  // Setup custom window handlers so we can override back
  window_set_click_config_provider_with_context(window, click_config_provider, this);
  layer_add_child(window_layer, menu_layer_get_layer(this->menu_layer));
}

static void window_unload(Window* window) {
  MenuWindow* this = base_window_get_parent(window_get_user_data(window));
  menu_layer_destroy(this->menu_layer); this->menu_layer = NULL;
}

MenuWindow* menu_window_create(EventManager* event_manager) {
  MenuWindow* this = malloc(sizeof(MenuWindow));
  this->base = base_window_create(this, (AppMessageInboxReceived) inbox_handler);
  this->event_manager = event_manager;
  this->num_rows = 3;

  Window* window = base_window_get_window(this->base);
  window_set_user_data(window, this->base);

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });

  return this;
}

void menu_window_destroy(MenuWindow* this) {
  if (!this) return;

  if (this->menu_layer) menu_layer_destroy(this->menu_layer);
  if (this) free(this);

  // Set pointer to NULL (no dangling pointers for us)
  this = NULL;
}

BaseWindow* menu_window_get_base(MenuWindow* this) {
  return this->base;
}