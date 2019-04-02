#include "input.h"

static bool is_float(char *number) {
	bool is_dot = false;

	if(isdigit(*number)) {
		number++;		
	} else {
		return false;
	}

	while(number != NULL) {
		if(isdigit(*number)) {
			number++;
		} else if(*number == "." && is_dot == false) {
			is_dot = true;
			number++;
		} else (
			return false;
		)
	}

	return true;
}

static bool is_decimal(char *number) {
	while(number != NULL) {
		if(!isdigit(*number)) {
			return false;
		}

		number++;
	}

	return true;
}

int input_result(int argc, char *argv[]) {
	if(argc == 1) {
		return NO_DATA_ON_INPUT;		
	}

	FILE *input_file = fopen(argv[1], "r");

	if(input_file == NULL) {
		return FILE_NOT_RECOGNIZED;
	} else {
		fclose(input_file);
	}

	if(argc == 2) {
		return NO_CURRENCY_NUMBER;
	}

	if(!is_decimal(argv[2])) {
		return CURRENCY_NUMBER_INCORRECT;
	}

	if(argc == 3) {
		return LOAD_DEFAULT_PARAMS;
	}

	if(!is_float(argv[2])) {
		return VALUE_NUMBER_INCORRECT;
	}

	if(argc == 4) {
		return LOAD_DEFAULT_CURRENCIES;
	}

	if(argc == 5) {
		return OUTPUT_ID_NOT_GIVEN;	
	}

	return 0;
}

void input_help() {
	printf("\n");
}
