#include "corewar.h"

void		cmd_and(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{	
	long int	arg_info1;
	long int	arg_info2;
	unsigned char	t_reg;
	int		pos;

	if (LOG_MODE)
		ft_printf("CMD_and\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info(mem, cmd_info->arg1, &arg_info1, &pos, cursor))
		return ;
	if (!load_arg_info(mem, cmd_info->arg2, &arg_info2, &pos, cursor))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = arg_info1 & arg_info2;
	if (cursor->r[t_reg] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		cmd_or(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int	arg_info1;
	long int	arg_info2;
	unsigned char	t_reg;
	int		pos;

	if (LOG_MODE)
		ft_printf("CMD_or\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info(mem, cmd_info->arg1, &arg_info1, &pos, cursor))
		return ;
	if (!load_arg_info(mem, cmd_info->arg2, &arg_info2, &pos, cursor))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = arg_info1 | arg_info2;
	if (cursor->r[t_reg] == 0) 
		cursor->carry = 1;
	else
		cursor->carry = 0;
}

void		cmd_xor(unsigned char *mem, t_cursor *cursor, t_cmd_info *cmd_info)
{
	long int	arg_info1;
	long int	arg_info2;
	unsigned char	t_reg;
	int		pos;

	if (LOG_MODE)
		ft_printf("CMD_xor\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info(mem, cmd_info->arg1, &arg_info1, &pos, cursor))
		return ;
	if (!load_arg_info(mem, cmd_info->arg2, &arg_info2, &pos, cursor))
		return ;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	cursor->r[t_reg] = arg_info1 ^ arg_info2;
	if (cursor->r[t_reg] == 0) 
		cursor->carry = 1;
	else
		cursor->carry = 0;
}
