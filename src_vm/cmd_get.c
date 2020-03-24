#include "corewar.h"

long int		get_t_dir4(unsigned char *mem, int pos)
{
	long int	t_dir;

	t_dir = 0;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 00 00 12 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 00 12 34 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 12 34 56 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos]; // 12 34 56 78;
	return (t_dir);
}

short int		get_t_dir2(unsigned char *mem, int pos)
{
	short int	t_dir;

	t_dir = 0; // 00 00
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 12 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	return (t_dir);
}

unsigned char	get_t_reg(unsigned char *mem, int pos)
{
	unsigned char	t_reg;

	pos += 1;
	pos %= MEM_SIZE;
	t_reg = mem[pos];
	return (t_reg);
}

long int		get_t_dir4_inplace(unsigned char *mem, int pos)
{
	long int	t_dir;

	t_dir = 0;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 00 00 12 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 00 12 34 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos];
	t_dir <<= 8; // 12 34 56 00;
	pos += 1;
	pos %= MEM_SIZE;
	t_dir += mem[pos]; // 12 34 56 78;
	return (t_dir);
}
