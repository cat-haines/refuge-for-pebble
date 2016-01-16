#pragma once

#include "refuge.h"

typedef struct {
  BaseWindow* base;
  GBitmap* bitmap;
  BitmapLayer* bitmap_layer;
  TextLayer* message_layer;
  char message_text[32];
} SplashWindow; 

SplashWindow* splash_window_create(char* init_message, int length);
void splash_window_destroy(SplashWindow* splash_window);

void splash_window_set_message(SplashWindow* splash_window, char* message, int length);
void splash_window_clear_message(SplashWindow* splash_window);

BaseWindow* splash_window_get_base(SplashWindow* splash_window);
