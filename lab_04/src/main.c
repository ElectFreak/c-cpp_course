#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clist.h"

typedef struct point {
  int x, y;
  struct intrusive_node node;
} point;

void add_point(intrusive_list* list, int x, int y) {  
  point* point_to_add = malloc(sizeof(point));
  point_to_add->x = x;
  point_to_add->y = y;

  add_node(list, &point_to_add->node);
}

void remove_point(intrusive_list* list, int x, int y) { // removes all (x, y) pairs
  intrusive_node* curr_node = list->head.next;
  point* curr_point;

  while (curr_node != &list->head) {
    curr_point = container_of(curr_node, struct point, node);
    curr_node = curr_node->next;

    if ((curr_point->x == x) && (curr_point->y == y)) {
      remove_node(list, &curr_point->node);
      free(curr_point);
    } 
  }
}

void show_all_points(intrusive_list* list) {
  intrusive_node* curr_node = list->head.next;
  
  point* curr_point; 

  while (curr_node != &list->head) {
    curr_point = container_of(curr_node, struct point, node);
    printf("(%d %d)", curr_point->x, curr_point->y);
    curr_node = curr_node->next;
    if (curr_node != &list->head) 
      printf(" ");
  }

  printf("\n");
}

void remove_all_points(intrusive_list* list) {
  intrusive_node* curr_node = list->head.next;

  while (curr_node != &list->head) {
    point* point = container_of(curr_node, struct point, node);
    curr_node = curr_node->next;
    remove_node(list, &point->node);
    free(point);
  }
}

int main() {
  intrusive_list list;
  init_list(&list);

  while (1) {
    char command[239];
    scanf("%239s", command);
    if (strcmp(command, "exit") == 0) {
      remove_all_points(&list);
      break;
    } else if (strcmp(command, "add") == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      add_point(&list, x, y);
    } else if (strcmp(command, "rm") == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      remove_point(&list, x, y);
    } else if (strcmp(command, "print") == 0) {
      show_all_points(&list);
    } else if (strcmp(command, "rma") == 0) {
      remove_all_points(&list);
    } else if (strcmp(command, "len") == 0) {
      printf("%d\n", get_length(&list));
    } else {
      printf("Unknown command\n");
    }

  }

  return 0;
}