int main(int argc, char* argv) {
	int result = input_result(argc, argv);

	switch(result) {
		case NO_DATA_ON_INPUT:
			printf("[ERROR] Data has not been delivered to the program.\n");
			input_help();
			return 1;
		case FILE_NOT_RECOGNIZED:
			printf("[ERROR] Recognition of the delivered file failed.\n");
			input_help();
			return 1;
		case NO_CURRENCY_NUMBER:
			printf("[ERROR] Lack of currency number.\n");
			input_help();
			return 1;
		case CURRENCY_NUMBER_INCORRECT:
			printf("[ERROR] Given currency number is incorrect.\n");
			input_help();
			return 1;
		case LOAD_DEFAULT_PARAMS:
			printf("Program has been loaded with default parametres.\n");
			//TODO wywołanie z domyślnymi parametrami (kwota, wejściowa oraz wyjściowa waluta)
			break;
		case VALUE_NUMBER_INCORRECT:
			printf("[ERROR] Given value number is incorrect.\n");
			input_help();
			return 1;
		case LOAD_DEFAULT_CURRENCIES:
			printf("Program has been loaded with default currencies.\n");
			//TODO wywołanie z domyślnymi walutami
			break;
		case OUTPUT_ID_NOT_GIVEN:
			printf("Id of output currency not given. Loading id currency which is not id of given input currency.");
			//TODO wywołanie z danymi argumentami oraz walutą wyjściową inną niż wejściową
			break;
		default:
		//TODO wywołanie z wszystkimi argumentami	
	}

	


	return 0;
}
