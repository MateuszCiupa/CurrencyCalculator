#include "algorithm.h"

static int get_head_index(head_t graph[], int size, char *input_marker) {
	for(int i = 0; i < size; i++) {
		if(!strcmp(graph[i].node.marker, input_marker)) {
			return i;
		}
	}

	return -1;
}

static int set_elem_path_value(double head_value, elem_t *elem) {
	double value = head_value * elem->denom_cost;
	value = elem->fee_type ? value - elem->fee : value - value * elem->fee / 100;

	if(value > elem->node->path_value) {
		elem->node->path_value = value;
		return 1;
	}

	return 0;
}

static void set_head_path_values(head_t *head, char *input_marker) {
	elem_t *neighbor = head->next;

	if(head->node.path_value == 0.0) {
		return;
	}
	
	while(neighbor != NULL) {
		if(!strcmp(neighbor->node->marker, input_marker) || is_marker_in_stack(head->node.path, neighbor->node->marker)) {
			neighbor = neighbor->next;
		} else {
			if(set_elem_path_value(head->node.path_value, neighbor)) {
				change_stack(&(neighbor->node->path), head->node.path);
				put(&(neighbor->node->path), head->node.marker);
			}

			neighbor = neighbor->next;
		}
	}
}

static int set_head_path_values_arbitrage(head_t *head, char *input_marker) {
	elem_t *neighbor = head->next;
	
	if(head->node.path_value == 0.0) {
		return 0;
	}

	while(neighbor != NULL) {
		if(set_elem_path_value(head->node.path_value, neighbor)) {
			change_stack(&(neighbor->node->path), head->node.path);
			put(&(neighbor->node->path), head->node.marker);

			if(!strcmp(neighbor->node->marker, input_marker)) {
				return 1;
			}
		}	

		neighbor = neighbor->next;	
	}

	return 0;
}

result_t get_path_value(head_t graph[], int size, input_t input) {
	result_t result;

	int input_index = get_head_index(graph, size, input.input_marker);
	int output_index = get_head_index(graph, size, input.output_marker);
	head_t *input_head = &graph[input_index];
	head_t *output_head = &graph[output_index];

	input_head->node.path_value = input.input_value;

	for(int i = 0; i < size - 2; i++) {
		set_head_path_values(input_head, input.input_marker);

		for(int i = 0; i < input_index; i++) {
			set_head_path_values(&graph[i], input.input_marker);
		}

		for(int i = input_index + 1; i < size; i++) {
			set_head_path_values(&graph[i], input.input_marker);
		}
	}

	put(&(graph[output_index].node.path), input.output_marker);

	result.input_value = input.input_value;
	result.path_value = output_head->node.path_value;
	result.path = output_head->node.path;

	return result;
}

static double get_arbitrage_result(head_t graph[], int size, input_t input) {
	int input_index = get_head_index(graph, size, input.input_marker);
	head_t *input_head = &graph[input_index];

	input_head->node.path_value = input.input_value;

	for(int i = 0; i < size - 1; i++) {
		set_head_path_values_arbitrage(input_head, input.input_marker);

		for(int i = 0; i < input_index; i++) {
			if(set_head_path_values_arbitrage(&graph[i], input.input_marker)) {
				put(&(input_head->node.path), input.input_marker);
				return input_head->node.path_value;
			}
		}

		for(int i = input_index + 1; i < size; i++) {
			if(set_head_path_values_arbitrage(&graph[i], input.input_marker)) {
				put(&(input_head->node.path), input.input_marker);
				return input_head->node.path_value;
			}
		}
	}

	put(&(input_head->node.path), input.input_marker);

	return input_head->node.path_value;;
}

void set_path_values_arbitrage(head_t graph[], int size, double input_value, result_t arbitrage_result[]) {
	input_t input;
	input.input_value = input_value;

	for(int i = 0; i < size; i++) {
		input.input_marker = graph[i].node.marker;
		arbitrage_result[i].input_value = input_value;
		init(&(arbitrage_result[i].path));
		arbitrage_result[i].path_value = get_arbitrage_result(graph, size, input);
		change_stack(&(arbitrage_result[i].path), graph[i].node.path);
		reset_graph(graph, size);
	}
}

void print_result(result_t result) {
	printf("Starting value: %f\n", result.input_value);
	printf("Most optimal path: ");
	print_stack(result.path);
	printf("Path value: %f\n", result.path_value);

}

void free_results(result_t results[], int size) {
	for(int i = 0; i < size; i++) {
		free_stack(&(results[i].path));
	}
}
