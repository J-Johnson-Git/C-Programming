#include "header.h"

/*
	Calculates the index of the entry into the BTB if a branch/jump occurs.
	The entry number is calculated using the last three chars of the address.

	Example:

	current_PC: 4001c4 -> 1c4 -> 1*16^2 + 12*16^1 + 4 = 452 -> 452 / 4 = 113
	next_PC:    4202b0
*/

int index_calc(char* address)
{
	int index = 0;
	int to_int = 0;
	int sixteen_sqr = 16 * 16;  //16^2, then 16^1, then 16^0
	address += 3;  //skip the first 3 chars of address

	for (int i = 0; i < 3; i++)  //examine the last three chars of the address
	{
		to_int = (*address > '9') ? ((*address & ~0x20) - 'A' + 10) : (*address - '0');  //converts char hex to int
		index += sixteen_sqr * to_int;
		address++;
		sixteen_sqr /= 16;
	}

	index /= 4;
	return index;
}
