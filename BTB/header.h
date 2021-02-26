#ifndef header_h
#define header_h

/*
	Program to create a Branch Target Buffer using a .txt file with program counter values from
	an arbitrary program run
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDRESS_LENGTH 7  //length of address string with room for \0 char "400190\n\0"
#define BTB_SIZE 1024
#define INPUT_FILE "full_trace.txt"
#define OUTPUT_FILE "BTB_array_results.txt"

//enum definition for state machine states
enum default_states
{
	PREDICT_TAKEN_ONE,      //0b00
	PREDICT_TAKEN_TWO,      //0b01
	PREDICT_NOT_TAKEN_ONE,  //0b10
	PREDICT_NOT_TAKEN_TWO   //0b11
};

//enum definition for state machine events
enum default_events
{
	TAKEN,
	NOT_TAKEN
};

//BTB struct definition, array declaration
struct BTB
{
	int entry;
	char current_PC[ADDRESS_LENGTH];
	char next_PC[ADDRESS_LENGTH];
	enum default_states default_state;
} BTB_array[BTB_SIZE];

//statistics variables struct definition, declaration
struct statistics
{
	int instruction_count;  //amount of instructions processed
	int hit;                //current_PC is in BTB
	int miss;               //current_PC is not in BTB
	int right;              //branch prediction was correct
	int wrong;              //branch prediction was not correct
	int branches_taken;     //number of total branches taken
	int collision;          //current_PC is not in BTB, branch taken, but entry used by other branch address
	int wrong_address;      //Prediction is taken, current_PC is in BTB, branches to a different location
} stats;

void scan_trace(FILE* input_file);
int index_calc(char* address);
void print_BTB(FILE* output_file);
const char* dec_to_bin(int state);
void default_next_state(enum default_events event, enum default_states* state);

#endif
