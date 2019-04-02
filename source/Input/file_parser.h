#ifndef _FILE_PARSER
#define _FILE_PARSER

#define MAX_FULL_NAME_SIZE 30
#define MARKER_SIZE 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Memory/stack.h"

typedef struct {
	double path_value;
	stack_t path;
	int currency_id;
	char *marker;
	char *full_name;
} node_t;

struct elem {
	node_t *node;
	int denom_id;
	double denom_cost; // denomination cost
	int fee_type;
	double fee;
	struct elem *next;
}; 

typedef struct elem elem_t;

typedef struct {
	node_t node;
	elem_t *next;
} head_t;

void set_graph(FILE *input_file, head_t graph[], int size);
void free_graph(head_t graph[], int size);
void write_graph(head_t graph[], int size);
void reset_graph(head_t graph[], int size);

#endif // _FILE_PARSER
