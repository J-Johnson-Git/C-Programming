#include "header.h"

int main(void)
{
	FILE* input_file;
	input_file = fopen("full_trace.txt", "r");

	FILE* output_file;
	output_file = fopen("BTB_array_results.txt", "w+");

	scan_trace(input_file);
	print_BTB(output_file);

	fclose(output_file);
	fclose(input_file);
	return 0;
}
