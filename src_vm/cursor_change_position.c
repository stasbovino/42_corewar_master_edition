#include "corewar.h"

void		cursor_change_position(t_cursor *list, int shift)
{
	if (list)
	{
		list->position += shift;
		list->position %= MEM_SIZE;
		if (list->position < 0)
			list->position = MEM_SIZE + list->position;
	}
}
