#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "../Memory/stack.h"
#include "../Input/file_parser.h"

typedef struct {
	double input_value;
	double path_value;
	stack_t path;
} result_t;

typedef struct {
	double input_value;
	char *input_marker;
	char *output_marker;
} input_t;

result_t get_path_value(head_t graph[], int size, input_t input);
void set_path_values_arbitrage(head_t graph[], int size, double input_value, result_t arbitrage_result[]);
void print_result(result_t result);
void free_results(result_t results[], int size);

#endif // _ALGORITHM_H
