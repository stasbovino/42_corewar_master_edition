#include "corewar.h"

unsigned char	*mem_buff_init(void)
{
	return ((unsigned char*)ft_strnew(MEM_SIZE));
}
