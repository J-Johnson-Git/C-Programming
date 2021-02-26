#include "header.h"

/*
	Prints out the contents of the BTB in formatted columns to the file "BTB_array_results.txt"

	Prints out statistics at end of file
*/

void print_BTB(FILE* output_file)
{
	fprintf(output_file, "%s", "Entry  Current_PC  Next_PC  Default Pred\n");
	if (strcmp(BTB_array[0].current_PC, "") != 0)  //if entry 0 isn't empty, print it. Can't use BTB_array[i].entry != 0 here
	{
		fprintf(output_file, "%d      ", BTB_array[0].entry);
		fprintf(output_file, "%s      ", BTB_array[0].current_PC);
		fprintf(output_file, "%s", BTB_array[0].next_PC);
		fprintf(output_file, "   %s\n", dec_to_bin(BTB_array[0].default_state));
	}

	for (int i = 1; i < BTB_SIZE; i++)
	{
		if (BTB_array[i].entry != 0)
		{
			if (BTB_array[i].entry < 10)
			{
				fprintf(output_file, "%d      ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s", BTB_array[i].next_PC);
				fprintf(output_file, "   %s\n", dec_to_bin(BTB_array[i].default_state));
			}
			else if ((BTB_array[i].entry >= 10) && (BTB_array[i].entry < 100))
			{
				fprintf(output_file, "%d     ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s", BTB_array[i].next_PC);
				fprintf(output_file, "   %s\n", dec_to_bin(BTB_array[i].default_state));
			}
			else if ((BTB_array[i].entry >= 100) && (BTB_array[i].entry < 1000))
			{
				fprintf(output_file, "%d    ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s", BTB_array[i].next_PC);
				fprintf(output_file, "   %s\n", dec_to_bin(BTB_array[i].default_state));
			}
			else
			{
				fprintf(output_file, "%d   ", BTB_array[i].entry);
				fprintf(output_file, "%s      ", BTB_array[i].current_PC);
				fprintf(output_file, "%s", BTB_array[i].next_PC);
				fprintf(output_file, "   %s\n", dec_to_bin(BTB_array[i].default_state));
			}

		}
	}

	fprintf(output_file, "\n");
	fprintf(output_file, "Instruction Count: %d\n", stats.instruction_count);
	fprintf(output_file, "Hits: %d\n", stats.hit);
	fprintf(output_file, "Misses: %d\n", stats.miss);
	fprintf(output_file, "Right: %d\n", stats.right);
	fprintf(output_file, "Wrong: %d\n", stats.wrong);
	fprintf(output_file, "Branches Taken: %d\n", stats.branches_taken);
	fprintf(output_file, "Collisions: %d\n", stats.collision);
	fprintf(output_file, "Wrong Addresses: %d\n", stats.wrong_address);
	fprintf(output_file, "Hit Rate: %.2lf%%\n", (double) (stats.hit) / (stats.hit + stats.miss) * 100);
	fprintf(output_file, "Prediction Accuracy: %.2lf%%\n", ((double) (stats.right) / (double) (stats.hit)) * 100);
	fprintf(output_file, "Incorrect Addresses: %.2lf%%\n", ((double) (stats.wrong_address) / (double) (stats.miss)) * 100);
}

//Supporting function that allows us to print out the prediction in 0b00 format instead of a decimal number
const char* dec_to_bin(int state)
{
	switch (state)
	{
		case 0:
			return "00";
		break;

		case 1:
			return "01";
		break;

		case 2:
			return "10";
		break;

		case 3:
			return "11";
		break;

		default:
			return "00";
		break;
	}
}
