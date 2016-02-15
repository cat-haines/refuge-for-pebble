#pragma once

#include <pebble.h>
#include "windows/base_window.h"
#include "windows/splash.h"
#include "windows/menu.h"
#include "windows/details.h"
#include "lib/events.h"

// App Messages
#define INBOX_SIZE  512
#define OUTBOX_SIZE 128

#define MSG_APP_READY     0
#define MSG_WASHROOMS     1
#define MSG_LOCATION_ERR  2
#define MSG_GET_ERR       3
#define MSG_DATA_LENGTH   4
#define MSG_NUM_PACKETS   5
#define MSG_DATA          6


// Text
#define TXT_INITIALIZING "Initializing..."
#define TXT_NO_CONNECTION "No Connection :("
#define TXT_CONNECTED "Fetching Data..."
#define TXT_NO_LOCATION "Location Services Disabled :("

// Events
#define APP_READY_EVENT       0
#define WASHROOMS_DATA_EVENT  1
#define NO_LOCATION_EVENT     2
#define SPLASH_BACK_EVENT     3
#define MENU_BACK_EVENT       4
