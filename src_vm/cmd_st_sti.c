#include "corewar.h"

void		cmd_st(unsigned char *mem, t_cursor *cursor,
		t_cmd_info *cmd_info, t_game_info *game_info)
{
	unsigned char	t_reg1;
	unsigned char	t_reg2;
	short int	t_ind;
	int		pos;

	if (LOG_MODE)	
		ft_printf("CMD_ST\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg1 = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg1))
		return ;
	pos += 1;
	pos %= MEM_SIZE;
	if (cmd_info->arg2 == IND_CODE)
	{
		t_ind = get_t_dir2(mem, pos);
		load_from_reg(cursor->r[t_reg1], mem, correct_pos(cursor->position + (t_ind % IDX_MOD)));
		if (game_info->color_mem)
			change_color_mem(correct_pos(cursor->position + (t_ind % IDX_MOD)), 4, game_info->color_mem, cursor->player_id);
		if (LOG_MODE)	
			ft_printf("_reg = %d, _ind = %d\n", t_reg1, t_ind);
	}
	else if (cmd_info->arg2 == REG_CODE)
	{
		t_reg2 = get_t_reg(mem, pos);
		if (!is_right_reg(t_reg2))
			return ;
		cursor->r[t_reg2] = cursor->r[t_reg1];
	}
}

void		cmd_sti(unsigned char *mem, t_cursor *cursor,
		t_cmd_info *cmd_info, t_game_info *game_info)
{
	long int	arg_info2;
	long int	arg_info3;
	unsigned char	t_reg;
	int		pos;

	if (LOG_MODE)	
		ft_printf("CMD_sti\n");
	pos = cursor->position;
	pos += 1;
	pos %= MEM_SIZE;
	t_reg = get_t_reg(mem, pos);
	if (!is_right_reg(t_reg))
		return ;
	pos += 1;
	pos %= MEM_SIZE;
	if (!load_arg_info2(mem, cmd_info->arg2, &arg_info2, &pos, cursor))
		return ;
	if (!load_arg_info2(mem, cmd_info->arg3, &arg_info3, &pos, cursor))
		return ;
	if (LOG_MODE)	
		ft_printf("_reg = %d, reg_value = %d (%d+%d)\n", t_reg, cursor->r[t_reg], arg_info2, arg_info3);
	load_from_reg(cursor->r[t_reg], mem, correct_pos(cursor->position + ((arg_info2 + arg_info3) % IDX_MOD)));
	if (game_info->color_mem)
		change_color_mem(correct_pos(cursor->position + ((arg_info2 + arg_info3) % IDX_MOD)),
			4, game_info->color_mem, cursor->player_id);
}
