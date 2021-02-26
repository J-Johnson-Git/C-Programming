#include "header.h"

int main(void)
{
	FILE* input_file;
	input_file = fopen(INPUT_FILE, "r");

	if (!input_file)
	{
		printf("unable to open input file");
		return -1;
	}

	FILE* output_file;
	output_file = fopen(OUTPUT_FILE, "w+");

	if (!output_file)
	{
		printf("unable to open output file");
		return -1;
	}

	scan_trace(input_file);
	print_BTB(output_file);

	fclose(output_file);
	fclose(input_file);
	return 0;
}
