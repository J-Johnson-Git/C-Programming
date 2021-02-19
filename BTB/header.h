#ifndef header_h
#define header_h

/*
	Program to create a Branch Target Buffer using a .txt file with program counter values from
	an arbitrary program run
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDRESS_LENGTH 7
#define BTB_SIZE 1024

//BTB struct definition, array declaration
struct BTB
{
	int entry;
	char current_PC[ADDRESS_LENGTH];
	char next_PC[ADDRESS_LENGTH];
} BTB_array[BTB_SIZE];

void scan_trace(FILE* input_file);
int index_calc(char* address);
void print_BTB(FILE* output_file);

#endif
