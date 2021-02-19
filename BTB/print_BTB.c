#include "header.h"

/*
	Prints out the contents of the BTB in formatted columns to the file "BTB_array_results.txt"
*/

void print_BTB(FILE* output_file)
{
	fprintf(output_file, "%s", "Entry  Current_PC  Next_PC\n");
	fprintf(output_file, "%d      ", BTB_array[0].entry);
	fprintf(output_file, "%s      ", BTB_array[0].current_PC);
	fprintf(output_file, "%s\n", BTB_array[0].next_PC);

	for (int i = 1; i < 1024; i++)
	{
		if (BTB_array[i].entry != 0)
		{
			if (BTB_array[i].entry < 10)
			{
				fprintf(output_file, "%d      ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s\n", BTB_array[i].next_PC);
			}
			else if ((BTB_array[i].entry >= 10) && (BTB_array[i].entry < 100))
			{
				fprintf(output_file, "%d     ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s\n", BTB_array[i].next_PC);
			}
			else if ((BTB_array[i].entry >= 100) && (BTB_array[i].entry < 1000))
			{
				fprintf(output_file, "%d    ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s\n", BTB_array[i].next_PC);
			}
			else
			{
				fprintf(output_file, "%d   ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s\n", BTB_array[i].next_PC);
			}

		}
	}
}
