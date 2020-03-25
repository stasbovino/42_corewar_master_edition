/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:23:28 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:23:56 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_game(t_cursor **cursor_list,
		t_game_info *game, unsigned char **mem)
{
	if (cursor_list && *cursor_list)
	{
		cursor_list_free(*cursor_list);
		(*cursor_list) = NULL;
	}
	if (mem && *mem)
	{
		free(*mem);
		(*mem) = NULL;
	}
	if (game && game->color_mem)
	{
		free(game->color_mem);
		game->color_mem = NULL;
	}
}
