#pragma once

#include "refuge.h"

typedef struct {
  Window *window;
  GBitmap *bitmap;
  BitmapLayer *bitmap_layer;
  TextLayer *message_layer;
  char message_text[32];
} SplashWindow; 

SplashWindow* splash_window_create(char* init_message, int length);
void splash_window_destroy(SplashWindow* window);

void splash_window_set_message(SplashWindow* window, char* message, int length);
void splash_window_clear_message(SplashWindow* window);

Window* splash_window_get_window(SplashWindow* window);
