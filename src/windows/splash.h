#pragma once

#include "refuge.h"
#include "../lib/events.h"

#define SPLASH_TIMEOUT  5000
#define MIN_TIME        1000  // Min time to display splash screen

typedef struct {
  BaseWindow* base;
  GBitmap* bitmap;
  BitmapLayer* bitmap_layer;
  TextLayer* message_layer;
  char message_text[32];

  bool min_time;
  bool connected;
  
  EventManager* event_manager;

  AppTimer* min_time_timer;
  AppTimer* timeout_timer;
} SplashWindow; 

SplashWindow* splash_window_create(EventManager* event_manager, char* init_message, int length);
void splash_window_destroy(SplashWindow* splash_window);

void splash_window_set_message(SplashWindow* splash_window, char* message, int length);
void splash_window_clear_message(SplashWindow* splash_window);

BaseWindow* splash_window_get_base(SplashWindow* splash_window);
