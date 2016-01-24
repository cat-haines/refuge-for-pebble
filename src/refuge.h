#pragma once

#include <pebble.h>
#include "windows/base_window.h"
#include "windows/splash.h"
#include "windows/menu.h"
#include "windows/details.h"
#include "lib/events.h"

// App Messages
#define INBOX_SIZE 128
#define OUTBOX_SIZE 128

#define MSG_APP_READY 0

// Text
#define TXT_INITIALIZING "Initializing..."
#define TXT_NO_CONNECTION "No Connection :("
#define TXT_CONNECTED "Connected!"