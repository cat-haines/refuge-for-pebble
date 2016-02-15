#include "refuge.h"
#include "menu.h"

MenuItem* menu_item_create(int distance, char* name, int name_len) {
  MenuItem* this = malloc(sizeof(MenuItem));

  this->distance = distance;

  this->name = malloc(name_len);
  memcpy(this->name, name, name_len);

  this->subtitle = malloc(16);
  snprintf(this->subtitle, 16, "%d.%02d miles away", distance / 100, distance % 100);

  return this;
}

void menu_item_destroy(MenuItem *this) {
  if (this->name) free(this->name);
  if (this->subtitle) free(this->subtitle);

  free(this);
  this = NULL;
}

static void inbox_handler(DictionaryIterator* iter, void* context) {
  MenuWindow* this = base_window_get_parent(context);

  // Grab the data we need:
  Tuple *num_packets_tuple = dict_find(iter, MSG_NUM_PACKETS);
  Tuple *data_tuple = dict_find(iter, MSG_DATA);

  // Make sure we have the data we expected
  if (!(num_packets_tuple && data_tuple)) {
    APP_LOG(APP_LOG_LEVEL_WARNING, "Expected packet with MSG_NUM_PACKETS, and MSG_DATA");
    return;
  }

  event_manager_raise_event(this->event_manager, WASHROOMS_DATA_EVENT);

  uint8_t num_packets = num_packets_tuple->value->uint8;

  char* data = data_tuple->value->cstring;
  int position = 0;

  // If we already have a list, clear it
  if (this->items) free(this->items);
  this->items = malloc(sizeof(MenuItem*) * num_packets);

  // Declare variables for the for loop
  int distance, name_len;
  // For num_packets
  for(int i = 0; i < num_packets; i++) {
    // distnace = next_byte
    // name_len = next byte
    distance = data[position++];
    name_len = data[position++];

    MenuItem* item = menu_item_create(distance, data+position, name_len+1);
    item->name[name_len] = '\0';
    this->items[i] = item;

    position += name_len;
  }

  APP_LOG(APP_LOG_LEVEL_DEBUG, "HERE!");
  menu_layer_reload_data(this->menu_layer);
  this->num_rows = num_packets;
}

static uint16_t menu_get_num_rows(MenuLayer *menu_layer, uint16_t section_index, void* context) {
  MenuWindow* this = context;
  return this->num_rows;
}

static void menu_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void* context) {
  MenuWindow* this = context;

  if (cell_index->row < this->num_rows) {
    MenuItem* this_row = this->items[cell_index->row];
    menu_cell_basic_draw(ctx, cell_layer, this_row->name, this_row->subtitle, NULL);
  }
}

static void on_down_click(ClickRecognizerRef recognizer, void* context) {
  MenuWindow* this = context;
  menu_layer_set_selected_next(this->menu_layer, false, MenuRowAlignCenter, false);
  menu_layer_reload_data(this->menu_layer);
}

static void on_up_click(ClickRecognizerRef recognizer, void* context) {
  MenuWindow* this = context;
  menu_layer_set_selected_next(this->menu_layer, true, MenuRowAlignCenter, false);
  menu_layer_reload_data(this->menu_layer);
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
  menu_layer_set_normal_colors(this->menu_layer, GColorWhite, GColorIndigo);
  menu_layer_set_highlight_colors(this->menu_layer, GColorIndigo, GColorWhite);
  menu_layer_set_callbacks(this->menu_layer, this, (MenuLayerCallbacks){
    .get_num_rows = menu_get_num_rows,
    .draw_row = menu_draw_row,
  });

  // Setup custom window handlers so we can override back
  window_set_click_config_provider_with_context(window, click_config_provider, this);
  // menu_layer_set_click_config_onto_window(this->menu_layer, window);
  layer_add_child(window_layer, menu_layer_get_layer(this->menu_layer));
}

static void window_unload(Window* window) {
  MenuWindow* this = base_window_get_parent(window_get_user_data(window));
  menu_layer_destroy(this->menu_layer); this->menu_layer = NULL;

  if(this->items) {
    for(int i = 0; i < this->num_rows; i++) {
      menu_item_destroy(this->items[i]);
      this->items[i] = 0;
    }
    free(this->items); this->items = NULL;
  }
}

MenuWindow* menu_window_create(EventManager* event_manager) {
  MenuWindow* this = malloc(sizeof(MenuWindow));
  this->base = base_window_create(this, (AppMessageInboxReceived) inbox_handler, 'm');
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
  if(this->items) {
    for(int i = 0; i < this->num_rows; i++) {
      menu_item_destroy(this->items[i]);
      this->items[i] = 0;
    }
    free(this->items); this->items = NULL;
  }

  if (this) free(this);

  // Set pointer to NULL (no dangling pointers for us)
  this = NULL;
}

BaseWindow* menu_window_get_base(MenuWindow* this) {
  return this->base;
}