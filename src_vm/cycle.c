/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:17:19 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:18:48 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	is_right_command(unsigned char command)
{
	if (command >= 0x01 && command <= 0x10)
		return (1);
	return (0);
}

int	is_args_type_req(unsigned char cmd)
{
	if (cmd == 0x01 || cmd == 0x09 || cmd == 0x0c || cmd == 0x0f)
		return (0);
	return (1);
}

int	number_of_args(unsigned char cmd)
{
	if (cmd == 0x02 || cmd == 0x0d)
		return (2);
	else if (cmd == 0x03)
		return (2);
	else if (cmd == 0x05 || cmd == 0x04)
		return (3);
	else if (cmd == 0x06 || cmd == 0x07 || cmd == 0x08)
		return (3);
	else if (cmd == 0x0a || cmd == 0x0e)
		return (3);
	else if (cmd == 0x0b)
		return (3);
	else if (cmd == 0x10)
		return (1);
	return (1);
}

int	is_right_args(unsigned char cmd,
			unsigned char a1, unsigned char a2, unsigned char a3)
{
	if ((cmd == 0x02 || cmd == 0x0d) &&
			(a1 == DIR_CODE || a1 == IND_CODE) && a2 == REG_CODE)
		return (2);
	else if (cmd == 0x03 &&
			(a2 == REG_CODE || a2 == IND_CODE) && a1 == REG_CODE)
		return (2);
	else if ((cmd == 0x05 || cmd == 0x04) && a1 == REG_CODE
				&& a2 == REG_CODE && a3 == REG_CODE)
		return (3);
	else if ((cmd == 0x06 || cmd == 0x07 || cmd == 0x08)
				&& a1 != 0 && a2 != 0 && a3 == REG_CODE)
		return (3);
	else if ((cmd == 0x0a || cmd == 0x0e) && a1 != 0 &&
				(a2 == REG_CODE || a2 == DIR_CODE) && a3 == REG_CODE)
		return (3);
	else if (cmd == 0x0b && a1 == REG_CODE && a2 != 0
				&& (a3 == REG_CODE || a3 == DIR_CODE))
		return (3);
	else if (cmd == 0x10 && a1 == REG_CODE)
		return (1);
	else
		return (0);
}

int	find_t_dir_size(unsigned char cmd)
{
	if (cmd >= 0x01 && cmd <= 0x08)
		return (4);
	if (cmd == 0x0d)
		return (4);
	if (cmd == 0x10)
		return (4);
	return (2);
}

int	arg_size(unsigned char arg, unsigned char size)
{
	if (arg == DIR_CODE)
		return (size);
	else if (arg == REG_CODE)
		return (1);
	else if (arg == IND_CODE)
		return (2);
	return (0);
}

int	count_shift(t_cmd_info *info)
{
	int	total;

	total = 2 + arg_size(info->arg1, info->dir_size);
	if (info->n_args >= 2)
		total += arg_size(info->arg2, info->dir_size);
	if (info->n_args == 3)
		total += arg_size(info->arg3, info->dir_size);
	return (total);
}

int	load_cmd_info(t_cmd_info *info, unsigned char *mem, t_cursor *cursor)
{
	int	temp_pos;

	temp_pos = cursor->position;
	info->id = cursor->command;
	temp_pos += 1;
	temp_pos %= MEM_SIZE;
	info->arg1 = (mem[temp_pos] & 0xc0) >> 6;
	info->arg2 = (mem[temp_pos] & 0x30) >> 4;
	info->arg3 = (mem[temp_pos] & 0xc) >> 2;
	info->dir_size = find_t_dir_size(info->id);
	info->n_args = number_of_args(info->id);
	return (is_right_args(info->id, info->arg1, info->arg2, info->arg3));
}

void	perform_command(unsigned char *mem,
			t_cursor *cursor, t_game_info *game_info)
{
	t_cmd_info	cmd_info;

	if (!is_right_command(cursor->command))
	{
		cursor_change_position(cursor, 1);
	}
	else if (!is_args_type_req(cursor->command))
	{
		cursor_change_position(cursor, do_cmd_no_args(mem, cursor, game_info));
	}
	else if (load_cmd_info(&cmd_info, mem, cursor) != 0)
	{
		cursor_change_position(
				cursor,
				do_cmd_w_args(mem, cursor, &cmd_info, game_info));
	}
	else
	{
		cursor_change_position(cursor, count_shift(&cmd_info));
	}
}

int	command_delay(unsigned char cmd)
{
	if (cmd == 0x01 || cmd == 0x04 || cmd == 0x05 || cmd == 0x0d)
		return (10);
	if (cmd == 0x06 || cmd == 0x07 || cmd == 0x08)
		return (6);
	if (cmd == 0x02 || cmd == 0x03)
		return (5);
	if (cmd == 0x09)
		return (20);
	if (cmd == 0x0a || cmd == 0x0b)
		return (25);
	if (cmd == 0x0c)
		return (800);
	if (cmd == 0x0e)
		return (50);
	if (cmd == 0x0f)
		return (1000);
	if (cmd == 0x10)
		return (2);
	return (0);
}

int	do_cycle(unsigned char *mem, t_game_info *game_info)
{
	t_cursor	*cursor_list;

	cursor_list = *(game_info->orig_cursor_list);
	if (!cursor_list)
		return (0);
	while (cursor_list)
	{
		if (cursor_list->delay == 0)
		{
			cursor_list->command = mem[cursor_list->position];
			cursor_list->delay = command_delay(cursor_list->command);
		}
		if (cursor_list->delay > 0)
			cursor_list->delay--;
		if (cursor_list->delay == 0)
			perform_command(mem, cursor_list, game_info);
		cursor_list = cursor_list->next;
	}
	return (1);
}
