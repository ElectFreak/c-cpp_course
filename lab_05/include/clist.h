#ifndef CLIST_H_
#define CLIST_H_
#include <stddef.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
} intrusive_node;

typedef struct intrusive_list {
  struct intrusive_node head;
} intrusive_list;

void init_list(intrusive_list* list);
intrusive_node add_node(intrusive_list* list, intrusive_node* node);
void remove_node(intrusive_list* list, intrusive_node* node);

int get_length(intrusive_list* list);

void apply(intrusive_list *list, void (*op)(intrusive_node *node, void *data), void *data);

#endif