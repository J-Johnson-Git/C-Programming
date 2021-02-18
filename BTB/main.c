#include "header.h"

int main(void)
{
	FILE *input_file;
	input_file = fopen("trace_test.txt", "r");

	scan_trace(input_file);

	for (int i = 0; i < 1024; i++)
	{
		if (BTB_array[i].entry != 0)
		{
			printf("%d %s", BTB_array[i].entry, BTB_array[i].current_PC);
		}
	}

	fclose(input_file);
	return 0;
}
