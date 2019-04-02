#include "stack.h"

void init(stack_t *path) {
	path->stack = malloc(STACK_INIT_SIZE * sizeof(*(path->stack)));
	path->max_size = STACK_INIT_SIZE;
	path->actual_size = 0;
}

static void double_size(stack_t *path) {
	char **tmp = realloc(path->stack, path->max_size * 2 * sizeof(*(path->stack)));
	path->stack = tmp;
	path->max_size *= 2; 
}

void put(stack_t *path, char *marker) {
	if(path->actual_size >= path->max_size) {
		double_size(path);
	}

	*(path->stack + path->actual_size) = malloc(MARKER_SIZE * sizeof(**(path->stack)));
	strcpy(*(path->stack + path->actual_size), marker);
	path->actual_size++;
}

void free_stack(stack_t *path) {
	for(int i = 0; i < path->actual_size; i++) {
		free(*(path->stack + i));
	}

	free(path->stack);
}

void change_stack(stack_t *changed, stack_t path) {
	if(changed->actual_size < path.actual_size) {
		for(int i = changed->actual_size; i < path.actual_size; i++) {
			if(changed->actual_size >= changed->max_size) {
				double_size(changed);
			}

			*(changed->stack + i) = malloc(MARKER_SIZE * sizeof(**(changed->stack)));
		}
	} else {
		for(int i = path.actual_size; i < changed->actual_size; i++) {
			free(*(changed->stack + i));
		}
	}

	changed->actual_size = path.actual_size;

	for(int i = 0; i < changed->actual_size; i++) {
		strcpy(*(changed->stack + i), *(path.stack + i));
	}
}

void print_stack(stack_t path) {
	if(path.actual_size > 0) {
		printf("%s", *(path.stack));
	}

	for(int i = 1; i < path.actual_size; i++) {
		printf(" -> %s", *(path.stack + i));
	}

	printf("\n");
}

int is_marker_in_stack(stack_t path, char *marker) {
	for(int i = 0; i < path.actual_size; i++) {
		if(!strcmp(*(path.stack + i), marker)) {
			return 1;
		}
	}

	return 0;
}
