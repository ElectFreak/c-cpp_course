#include <stddef.h>

#include "clist.h"

void init_list(intrusive_list* list) {
  intrusive_node* head = &list->head;

  head->next = head;
  head->prev = head;

  return;
}

intrusive_node add_node(intrusive_list* list, intrusive_node* node) {
  intrusive_node* last = list->head.prev;
  last->next = node;
  node->prev = last;
  node->next = &list->head;
  list->head.prev = node;

  return *node;
}

void remove_node(intrusive_list* list, intrusive_node* node) {
  intrusive_node* next = node->next;
  intrusive_node* prev = node->prev;

  prev->next = next;
  next->prev = prev;

  return;
}

int get_length(intrusive_list* list) {
  int counter = 0;  
  intrusive_node* current = &list->head;
  while (current->next != &list->head) {
    counter++;
    current = current->next;  
  }
  return counter;
}

void apply(intrusive_list *list, void (*op)(intrusive_node* node, void* data), void* data) {
  intrusive_node* current = list->head.next;
  while (current != &list->head) {
    op(current, data);
    current = current->next;
  }
}