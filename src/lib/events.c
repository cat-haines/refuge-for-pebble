#include "events.h"

/****************************** PRIVATE ******************************/
static EventNode* event_node_create(int event_key, EventCallback callback) {
  EventNode* this = malloc(sizeof(EventNode));
  this->event_key = event_key;
  this->callback = callback;
  this->prev = NULL;
  this->next = NULL;

  return this;
}

static EventNode* event_manager_find_event(EventManager* events, int event_key) {
  if (!events) return NULL;

  EventNode* this = events->head;
  
  while(this) {
    if (this->event_key == event_key) return this;
    this = (EventNode*)this->next;
  }

  return NULL;
}

/****************************** PUBLIC ******************************/
EventManager* event_manager_create() {
  EventManager* this = malloc(sizeof(EventManager));
  this->head = NULL;
  this->tail = NULL;

  return this;
}

void event_manager_destroy(EventManager* events) {
  if (!events) return;

  EventNode* this = events->head;
  EventNode* next;

  while(this) {
    next = (EventNode*)this->next;
    free(this);
    this = next;
  }

  free(events);
}

void event_manager_subscribe(EventManager* events, int event_key, EventCallback callback) {
  if (!events) return;

  EventNode* node = event_manager_find_event(events, event_key);
  if (node) {
    node->callback = callback;
    return;
  }

  node = event_node_create(event_key, callback);
  if (!events->head) {
    events->head = node;
    events->tail = node;
  } else {
    node->prev = events->tail;
    events->tail->next = node;
    events->tail = node;
  }
}

void event_manager_unsubscribe(EventManager* events, int event_key) {
  if (!events) return;

  // Find the node and return if it doesn't
  EventNode* node = event_manager_find_event(events, event_key);
  if (!node) return;

  // Make sure there's a prev node (or update head if there isn't)
  if (node == events->head) {
    events->head = node->next;
  } else {
    node->prev->next = node->next;
  }

  // Make sure there's a next node (or update tail if there isn't)
  if (node == events->tail) {
    events->tail = node->prev;
  } else {
    node->next->prev = node->prev;
  }

  // destroy the node
  free(node);
}

void event_manager_raise_event(EventManager* events, int event_key) {
  event_manager_raise_event_with_context(events, event_key, NULL);
}

void event_manager_raise_event_with_context(EventManager* events, int event_key, void* context) {
  if (!events) return;

  EventNode* node = event_manager_find_event(events, event_key);

  if (!node) {
    APP_LOG(APP_LOG_LEVEL_INFO, "No event for event_key %d", event_key);
    return;
  }

  node->callback(context);
}