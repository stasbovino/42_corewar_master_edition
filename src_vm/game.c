/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:20:45 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:22:37 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_game(t_game_info *game, t_cursor **cursor_list,
		t_flags *flags, unsigned char *mem)
{
	game->current_cycle = 1;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->check_counter = 1;
	game->last_alive = (*cursor_list)->player_id;
	game->orig_cursor_list = cursor_list;
	game->live_count = 0;
	game->is_aff_flag = flags->aff;
	game->color_mem = NULL;
	game->dump = flags->for_dump;
	game->n_players = flags->count;
	game->n_cursors = game->n_players;
	game->next_cur_id = game->n_players + 1;
}

static void	print_regs(t_cursor *cursor_list)
{
	int i;

	i = 1;
	while (cursor_list)
	{
		ft_printf("player %d, pos %d: ",
				cursor_list->player_id, cursor_list->position);
		while (i <= REG_NUMBER)
		{
			ft_printf("[%d] ", cursor_list->r[i]);
			i++;
		}
		i = 1;
		cursor_list = cursor_list->next;
		ft_printf("\n");
	}
}

static void	test(t_game_info game, t_cursor *cursor_list, unsigned char *mem)
{
	mem_buff_print_w_cur(mem, cursor_list, 32);
	ft_printf("curr: %d\n", game.current_cycle);
	ft_printf("last alive: %d\n", game.last_alive);
	ft_printf("live count: %d\n", game.live_count);
	print_regs(cursor_list);
}

int			start_game(unsigned char *mem,
		t_cursor **cursor_list, t_flags *flags)
{
	t_game_info	game;

	init_game(&game, cursor_list, flags, mem);
	while (do_cycle(mem, &game))
	{
		if (game.cycles_to_die <= 0 || game.check_counter == game.cycles_to_die)
		{
			if (!do_check(game.orig_cursor_list, &(game.cycles_to_die), &game))
				break ;
			game.live_count = 0;
			game.check_counter = 0;
		}
		if (flags->for_dump != -1 && game.current_cycle == flags->for_dump)
		{
			mem_buff_print(mem, flags->dump_size);
			free_game(cursor_list, &game, &mem);
			return (-1);
		}
		++game.check_counter;
		++game.current_cycle;
	}
	ft_printf("total: %d\n", game.current_cycle);
	free_game(cursor_list, &game, &mem);
	return (game.last_alive);
}
