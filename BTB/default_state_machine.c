#include "header.h"

/*
	Default state machine to use for branch prediction.

	Start in PREDICT_TAKEN_ONE (0b00)
	if (TAKEN)
		Stay in PREDICT_TAKEN_ONE (0b00)
	if (NOT_TAKEN)
		Move to PREDICT_TAKEN_TWO (0b01)

	if in PREDICT_TAKEN_TWO (0b01)
	if (TAKEN)
		Move to PREDICT_TAKEN_ONE (0b00)
	if (NOT_TAKEN)
		Move to PREDICT_NOT_TAKEN_ONE (0b10)

	if in PREDICT_NOT_TAKEN_ONE (0b10)
	if (TAKEN)
		Move to PREDICT_TAKEN_TWO (0b01)
	if (NOT_TAKEN)
		Move to PREDICT_NOT_TAKEN_TWO (0b11)

	if in PREDICT_NOT_TAKEN_TWO (0b11)
	if (TAKEN)
		Move to PREDICT_NOT_TAKEN_ONE (0b10)
	if (NOT_TAKEN)
		Stay in PREDICT_NOT_TAKEN_TWO (0b11)
*/

void default_next_state(enum default_events event, enum default_states* state)
{
	switch (*state)
	{
		case PREDICT_TAKEN_ONE:
			switch (event)
			{
				case TAKEN:
					*state = PREDICT_TAKEN_ONE;
				break;

				case NOT_TAKEN:
					*state = PREDICT_TAKEN_TWO;
				break;

				default:
					*state = PREDICT_TAKEN_ONE;
				break;
			}
		break;

		case PREDICT_TAKEN_TWO:
			switch (event)
			{
				case TAKEN:
					*state = PREDICT_TAKEN_ONE;
				break;

				case NOT_TAKEN:
					*state = PREDICT_NOT_TAKEN_ONE;
				break;

				default:
					*state = PREDICT_TAKEN_TWO;
				break;
			}
		break;

		case PREDICT_NOT_TAKEN_ONE:
			switch (event)
			{
				case TAKEN:
					*state = PREDICT_TAKEN_TWO;
				break;

				case NOT_TAKEN:
					*state = PREDICT_NOT_TAKEN_TWO;
				break;

				default:
					*state = PREDICT_NOT_TAKEN_ONE;
				break;
			}
		break;

		case PREDICT_NOT_TAKEN_TWO:
			switch (event)
			{
				case TAKEN:
					*state = PREDICT_NOT_TAKEN_ONE;
				break;

				case NOT_TAKEN:
					*state = PREDICT_NOT_TAKEN_TWO;
				break;

				default:
					*state = PREDICT_NOT_TAKEN_TWO;
				break;
			}
		break;

		default:
			*state = PREDICT_TAKEN_ONE;
		break;
	}
}
