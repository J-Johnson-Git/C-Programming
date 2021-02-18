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
	char current_PC[ADDRESS_LENGTH + 1] = "";  //fgets needs to read \n chars for strcpy to copy correctly
	char next_PC[ADDRESS_LENGTH + 1] = "";

	fgets(current_PC, ADDRESS_LENGTH + 1, input_file);  //preload current_PC with first entry
	while (fgets(next_PC, ADDRESS_LENGTH + 1, input_file))
	{
		if (index_calc(next_PC) != (index_calc(current_PC) + 1))  //branch condition, adding to BTB
		{
			BTB_array[index_calc(current_PC)].entry = index_calc(current_PC);
			strcpy(BTB_array[index_calc(current_PC)].current_PC, current_PC);
			strcpy(BTB_array[index_calc(current_PC)].next_PC, next_PC);
		}
		strcpy(current_PC, next_PC);  //copy next_PC back into current_PC when finished with comparisons/calcs
	}

}
