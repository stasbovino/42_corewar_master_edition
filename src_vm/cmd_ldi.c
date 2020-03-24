#include "corewar.h"

void		cmd_ldi(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int	arg_info1;
	long int	arg_info2;
	unsigned char	t_reg;
	int		pos;

	if (LOG_MODE)	
		ft_printf("CMD_ldi arg1 = %d arg2 = %d\n", cmd_info->arg1, cmd_info->arg2);
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info2(mem, cmd_info->arg1, &arg_info1, &pos, cursor))
		return ;
	if (!load_arg_info2(mem, cmd_info->arg2, &arg_info2, &pos, cursor))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	if (LOG_MODE)	
		ft_printf("_reg[%d] = from(%d)+(%d)\n", t_reg, arg_info1, arg_info2);
	cursor->r[t_reg] = get_t_dir4_inplace(mem,
		correct_pos((cursor->position + ((arg_info1 + arg_info2) % IDX_MOD)) % MEM_SIZE));
	if (LOG_MODE)	
		ft_printf("_value = %d\n", cursor->r[t_reg]);
}

void		cmd_lldi(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int	arg_info1;
	long int	arg_info2;
	unsigned char	t_reg;
	int		pos;

	if (LOG_MODE)	
		ft_printf("CMD_lldi\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info2(mem, cmd_info->arg1, &arg_info1, &pos, cursor))
		return ;
	if (!load_arg_info2(mem, cmd_info->arg2, &arg_info2, &pos, cursor))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = get_t_dir4(mem,
		(cursor->position + (arg_info1 + arg_info2)) % MEM_SIZE);
}
