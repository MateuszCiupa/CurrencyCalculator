#include "algorithm.h"

int main(int argc, char *argv[]) {
	FILE *in = fopen(argv[1], "r");
	int size = atoi(argv[2]);

	head_t graph[size];
	set_graph(in, graph, size);

	input_t input;
	input.input_value = argc > 3 ? atof(argv[3]) : 1000.0;
	input.input_marker = argc > 4 ? argv[4] : "EUR";
	input.output_marker = argc > 5 ? argv[5] : "USD";

	result_t result1 = get_path_value(graph, size, input);
	print_result(result1);
	printf("\n");

	reset_graph(graph, size);

	result_t arbitrage_result[size];
	set_path_values_arbitrage(graph, size, input.input_value, arbitrage_result);

	for(int i = 0; i < size; i++) {
		print_result(arbitrage_result[i]);
		printf("\n");
	}

	free_graph(graph, size);
	free_results(arbitrage_result, size);

	return 0;
}
