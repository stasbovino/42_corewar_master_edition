/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:56:49 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:57:03 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	load_arg_info(unsigned char *mem, unsigned char arg, long int *arg_info, int *pos, t_cursor *cursor)
{
	short int	t_ind;
	int		tmp_pos;
	unsigned char	t_reg;

	if (arg == DIR_CODE)
	{
		(*arg_info) = get_t_dir4(mem, *pos);
		(*pos) += 4;
		(*pos) %= MEM_SIZE;
	}
	else if (arg == IND_CODE)
	{	
		t_ind = get_t_dir2(mem, *pos);
		tmp_pos = correct_pos(cursor->position + (t_ind % IDX_MOD));
		tmp_pos %= MEM_SIZE;
		(*arg_info) = get_t_dir4(mem, tmp_pos);
		(*pos) += 2;
		(*pos) %= MEM_SIZE;
	}
	else if (arg == REG_CODE)
	{
		t_reg = get_t_reg(mem, *pos);
		if (!is_right_reg(t_reg))
			return (0);
		(*arg_info) = cursor->r[t_reg];
		(*pos) += 1;
		(*pos) %= MEM_SIZE;
	}
	return (1);
}

int	load_arg_info2(unsigned char *mem, unsigned char arg, long int *arg_info, int *pos, t_cursor *cursor)
{
	short int		t_ind;
	unsigned char	t_reg;
	int				tmp_pos;

	if (arg == DIR_CODE)
	{
		(*arg_info) = get_t_dir2(mem, *pos);
		(*pos) += 2;
		(*pos) %= MEM_SIZE;
	}
	else if (arg == IND_CODE)
	{
		t_ind = get_t_dir2(mem, *pos);
		tmp_pos = correct_pos(cursor->position + (t_ind % IDX_MOD));
		tmp_pos %= MEM_SIZE;
		(*arg_info) = get_t_dir4(mem, tmp_pos);
		(*pos) += 2;
		(*pos) %= MEM_SIZE;
	}
	else if (arg == REG_CODE)
	{
		t_reg = get_t_reg(mem, *pos);
		if (!is_right_reg(t_reg))
			return (0);
		(*arg_info) = cursor->r[t_reg];
		(*pos) += 1;
		(*pos) %= MEM_SIZE;
	}
	return (1);
}

void	load_from_reg(int reg_info, unsigned char *mem, int place)
{
	place %= MEM_SIZE;
	mem[place] = (reg_info & 0xff000000) >> 24;
	place += 1;
	place %= MEM_SIZE;
	mem[place] = (reg_info & 0x00ff0000) >> 16;
	place += 1;
	place %= MEM_SIZE;
	mem[place] = (reg_info & 0x0000ff00) >> 8;
	place += 1;
	place %= MEM_SIZE;
	mem[place] = reg_info & 0x000000ff;
}
