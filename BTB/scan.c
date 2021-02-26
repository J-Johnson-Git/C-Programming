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
	//file scanning variables/index(entry) numbers
	char current_PC[ADDRESS_LENGTH] = "";  //fgets needs to read \n chars for strcpy to copy correctly
	char next_PC[ADDRESS_LENGTH] = "";
	char skip_newline = 0;
	int next_PC_index = 0;
	int current_PC_index = 0;

	fgets(current_PC, ADDRESS_LENGTH, input_file);  //preload current_PC with first entry
	skip_newline = fgetc(input_file);
	stats.instruction_count++;
	while (fgets(next_PC, ADDRESS_LENGTH, input_file))
	{
		//retrieve line, skip newline char, find index numbers
		skip_newline = fgetc(input_file);
		current_PC_index = index_calc(current_PC);
		next_PC_index = index_calc(next_PC);

		if (strcmp(current_PC, BTB_array[current_PC_index].current_PC) == 0)  //current_PC is in BTB
		{
			stats.hit++;
			if ((BTB_array[current_PC_index].default_state == PREDICT_TAKEN_ONE) || (BTB_array[current_PC_index].default_state == PREDICT_TAKEN_TWO))
			{
				if (strcmp(next_PC, BTB_array[current_PC_index].next_PC) == 0)  //next_PC == next_PC in current BTB entry
				{
					stats.branches_taken++;
					stats.right++;
					if (next_PC_index != (current_PC_index + 1))
					{
						default_next_state(TAKEN, &BTB_array[current_PC_index].default_state);
					}
					else
					{
						default_next_state(NOT_TAKEN, &BTB_array[current_PC_index].default_state);
					}
				}
				else  //branching to different location or not branching
				{
					stats.wrong++;
					if (next_PC_index != (current_PC_index + 1))  //branch condition
					{
						stats.branches_taken++;
						stats.wrong_address++;
						BTB_array[current_PC_index].default_state = PREDICT_TAKEN_ONE;
					}
					else  //not branching
					{
						default_next_state(NOT_TAKEN, &BTB_array[current_PC_index].default_state);
					}

				}
			}
			else  //predict branch not taken
			{
				if (next_PC_index == (current_PC_index + 1))  //branch not taken
				{
					stats.right++;
					default_next_state(NOT_TAKEN, &BTB_array[current_PC_index].default_state);
				}
				else  //branch taken
				{
					stats.branches_taken++;
					stats.wrong++;
					default_next_state(TAKEN, &BTB_array[current_PC_index].default_state);
				}
			}

			//update BTB entry
			BTB_array[current_PC_index].entry = current_PC_index;
			strcpy(BTB_array[current_PC_index].current_PC, current_PC);
			strcpy(BTB_array[current_PC_index].next_PC, next_PC);
		}
		else  //current_PC is not in BTB
		{
			if (next_PC_index != (current_PC_index + 1))  //miss condition, branch condition
			{
				if (strcmp(next_PC, BTB_array[current_PC_index].current_PC) != 0)  //collision condition
				{
					stats.collision++;
				}

				//update BTB entry with current info, incr miss, update state machines
				stats.branches_taken++;
				stats.miss++;
				default_next_state(TAKEN, &BTB_array[current_PC_index].default_state);
				BTB_array[current_PC_index].entry = current_PC_index;
				strcpy(BTB_array[current_PC_index].current_PC, current_PC);
				strcpy(BTB_array[current_PC_index].next_PC, next_PC);
			}
		}
		stats.instruction_count++;
		strcpy(current_PC, next_PC);  //copy next_PC back into current_PC when finished with comparisons
	}
}
