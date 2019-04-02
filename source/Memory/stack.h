#ifndef _STACK_H
#define _STACK_H

#define STACK_INIT_SIZE 20

typedef struct {
	char **stack;
	int max_size;
	int actual_size;
} stack_t;

void init(stack_t *path);
void put(stack_t *path, char *marker);
void change_stack(stack_t *changed, stack_t path); // with other stack
char *pop(stack_t *path);
void free_stack(stack_t *path);
void print_stack(stack_t path);
int is_marker_in_stack(stack_t path, char *marker);

#include "../Input/file_parser.h"

#endif // _STACK_H
