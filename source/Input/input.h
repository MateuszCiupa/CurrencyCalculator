#ifndef _INPUT_PARSER
#define _INPUT_PARSER

#define NO_DATA_ON_INPUT 1
#define FILE_NOT_RECOGNIZED 2
#define NO_CURRENCY_NUMBER 3
#define CURRENCY_NUMBER_INCORRECT 4
#define LOAD_DEFAULT_PARAMS 5
#define VALUE_NUMBER_INCORRECT 6
#define LOAD_DEFAULT_CURRENCIES 7
#define OUTPUT_ID_NOT_GIVEN 8

#define DEFAULT_INPUT_MONEY 1000

#include <stdio.h>

int input_result(int argc, char *input[]);
void input_help();

#endif // _INPUT_PARSER
