#include "header.h"

/*
	Scans through the trace .txt file and retrieves the addresses as char arrays.
	The current_PC array gets the first address in the trace, which moves the scanner onto
	the second one. The next_PC array gets the second address, and then each address after.

	The current_PC array always contains the address behind next_PC, so we can check for
	branches/jumps.
*/

void scan_trace(FILE *input_file)
{
	char current_PC[ADDRESS_LENGTH] = "";  //fgets needs to read \n chars for strcpy to copy correctly
	char next_PC[ADDRESS_LENGTH] = "";
	char skip_newline = 0;
	int next_PC_index = 0;
	int current_PC_index = 0;


	fgets(current_PC, ADDRESS_LENGTH, input_file);  //preload current_PC with first entry
	skip_newline = fgetc(input_file);
	while (fgets(next_PC, ADDRESS_LENGTH, input_file))
	{
		//retrieve line, skip newline char, find index numbers
		skip_newline = fgetc(input_file);
		current_PC_index = index_calc(current_PC);
		next_PC_index = index_calc(next_PC);

		if (next_PC_index != (current_PC_index + 1))  //branch condition, adding to BTB
		{
			BTB_array[current_PC_index].entry = current_PC_index;
			strcpy(BTB_array[current_PC_index].current_PC, current_PC);
			strcpy(BTB_array[current_PC_index].next_PC, next_PC);
		}

		strcpy(current_PC, next_PC);  //copy next_PC back into current_PC when finished with comparison
	}

}
