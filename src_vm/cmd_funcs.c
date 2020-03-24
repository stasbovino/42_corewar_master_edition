#include "corewar.h"

int			is_right_reg(unsigned char reg)
{
	if (reg >= 1 && reg <= REG_NUMBER)
		return (1);
	return (0);
}

int			correct_pos(int pos)
{
	pos %= MEM_SIZE; // not sure about negative %
	if (pos < 0)
		pos = MEM_SIZE + pos;
	return (pos);
}
