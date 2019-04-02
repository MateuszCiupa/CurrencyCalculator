#include "file_parser.h"

int main(int argc, char *argv[]) {
	FILE *in = fopen(argv[1], "r");
	int currency_no = atoi(argv[2]);
	head_t graph[currency_no];
	set_graph(in, graph, currency_no);
	write_graph(graph, currency_no);
	free_graph(graph, currency_no);
	return 0;
}
