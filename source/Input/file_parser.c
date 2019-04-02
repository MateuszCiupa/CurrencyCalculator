#include "file_parser.h"

static void make_head(head_t *head) {
	head->node.marker = malloc(MARKER_SIZE * sizeof (char));
	head->node.full_name = malloc(MAX_FULL_NAME_SIZE * sizeof (char));
	head->node.path_value = 0.0;
	head->next = NULL;
	init(&(head->node.path));
}

static node_t *get_node(head_t graph[], int size, char *marker) {
	for(int i = 0; i < size; i++) {
		if(!strcmp(graph[i].node.marker, marker)) {
			return &(graph[i].node);
		}
	}
}

static head_t *get_head(head_t graph[], int size, char *input_marker) {
	elem_t *elem, *parent;

	for(int i = 0; i < size; i++) {
		if(!strcmp(graph[i].node.marker, input_marker)) {
			return &(graph[i]);
		}
	}	

	return NULL;
}

void set_graph(FILE *input_file, head_t graph[], int size) {
	for(int i = 0; i < size; i++) {
		make_head(&graph[i]);
		fscanf(input_file, "%d", &(graph[i].node.currency_id));
		fscanf(input_file, "%s", graph[i].node.marker);
		fscanf(input_file, "%[^\n]", graph[i].node.full_name);
	}

	char *input_marker = malloc(MARKER_SIZE * sizeof (*input_marker));
	char *output_marker = malloc(MARKER_SIZE * sizeof (*output_marker));
	int denom_id;
	int scan_result = fscanf(input_file, "%d", &denom_id);
	elem_t *elem;
	head_t *head;

	while(scan_result != EOF) {
		fscanf(input_file, "%s", input_marker);

		head = get_head(graph, size, input_marker);
		elem = head->next;

		if(elem == NULL) {
			head->next = malloc(sizeof (*elem));
			elem = head->next;
		} else {
			while(elem->next != NULL) {
				elem = elem->next;
			}
				
			elem->next = malloc(sizeof (*elem));
			elem = elem->next;
		}

		elem->next = NULL;
		elem->denom_id = denom_id;

		fscanf(input_file, "%s", output_marker);
		elem->node = get_node(graph, size, output_marker);

		fscanf(input_file, "%lf", &(elem->denom_cost));
		fscanf(input_file, "%d", &(elem->fee_type));
		fscanf(input_file, "%lf", &(elem->fee));

		scan_result = fscanf(input_file, "%d", &denom_id);
	}

	free(input_marker);
	free(output_marker);
	fclose(input_file);
}

static void free_list(elem_t *list);

void free_graph(head_t graph[], int size) {
	for(int i = 0; i < size; i++) {
		free_list(graph[i].next);
		free(graph[i].node.marker);
		free(graph[i].node.full_name);
		free_stack(&(graph[i].node.path));
	}
}

static void free_list(elem_t *list) {
	elem_t *elem;

	while(list != NULL) {
		elem = list;
		list = list->next;
		free(elem);
	}
}

void write_graph(head_t graph[], int size) {
	for(int i = 0; i < size; i++) {
		printf("Head Id: %d, Marker: %s, Path value: %f\n", graph[i].node.currency_id, graph[i].node.marker, graph[i].node.path_value);
	
		elem_t *elem = graph[i].next;

		while(elem != NULL) {
			printf("*Denom Id: %d, Marker: %s, Path value: %f\n", elem->denom_id, elem->node->marker, elem->node->path_value);
			elem = elem->next;
		}

		printf("\n");
	}
}

void reset_graph(head_t graph[], int size) {
	for(int i = 0; i < size; i++) {
		graph[i].node.path_value = 0.0;
		free_stack(&(graph[i].node.path));
		init(&(graph[i].node.path));
	}
}
