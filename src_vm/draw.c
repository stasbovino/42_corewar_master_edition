#include "corewar.h"

static int	is_cur_pos(t_cursor *cur, int index)
{
	while (cur)
	{
		if (cur->position == index)
			return (cur->player_id + 1);
		cur = cur->next;
	}
	return (0);
}

static void	set_field(WINDOW *field, t_cursor *cursor, unsigned char *mem,
		unsigned char *color_mem)
{
	int y;
	int x;
	int i;
	int j;
	int width;
	int color;


	werase(field);
	width = 194;
	x = 1;
	y = 1;
	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		if (x + 2 < width - 1)
		{
			if (cursor && (color = is_cur_pos(cursor, i)))
			{
				color = (color >= 6) ? 6 : color;
				wattron(field, COLOR_PAIR(color));
				mvwprintw(field, y, x, "%.2hhx", mem[i]);
				wattroff(field, COLOR_PAIR(color));
			}
			else if (color_mem[i] != 0)
			{
				color = (color_mem[i] >= 6) ? 16 : color_mem[i] + 11;
				wattron(field, COLOR_PAIR(color));
				mvwprintw(field, y, x, "%.2hhx", mem[i]);
				wattroff(field, COLOR_PAIR(color));
			}
			else
			{
				wattron(field, COLOR_PAIR(20));
				mvwprintw(field, y, x, "%.2hhx", mem[i]);
				wattroff(field, COLOR_PAIR(20));
			}
			i++;
			x+=2;
		}
		if (x + 3 < width - 1)
		{
			mvwprintw(field, y, x, " ");
			x++;
		}
		else
		{
			mvwprintw(field, y, x, "\n");
			y++;
			x = 1;
		}
	}
	box(field, 0, 0);
	wrefresh(field);
}

static void	set_info(WINDOW *info, t_game_info *game, t_champ *champs)
{
	int n;
	int i;
	int color;

	n = 1;
	werase(info);
	wattron(info, (game->visual.pause == 0) ? COLOR_PAIR(9) : COLOR_PAIR(8));
	mvwprintw(info, n, 2, (game->visual.pause == 0) ? "Running" : "Paused ");
	wattroff(info, (game->visual.pause == 0) ? COLOR_PAIR(3) : COLOR_PAIR(2));
	mvwprintw(info, n += 2, 2, "Cycle: %d", game->current_cycle);
	mvwprintw(info, n += 2, 2, "Cursors: %d", game->n_cursors);
	i = 0;
	while (i < game->n_players)
	{
		color = (i >= 4) ? 6 : i + 2;
		wattron(info, COLOR_PAIR(color));
		mvwprintw(info, n += 3, 2, 
				"Player #%d, %s", champs[i].num, champs[i].name);
		i++;
		wattroff(info, COLOR_PAIR(color));
	}
	mvwprintw(info, n += 3, 2, "Last alive: #%d as %s", 
			game->last_alive, champs[game->last_alive - 1].name);
	mvwprintw(info, n += 2, 2, "Cycles_to_die: %d", game->cycles_to_die);
	mvwprintw(info, n += 2, 2, "Lives: %d", game->live_count);
	mvwprintw(info, n += 2, 2, "Cycles_to_check: %d", 
			game->cycles_to_die - game->check_counter);
	if (game->visual.game_over == 1)
	{
		color = (game->last_alive >= 6) ? 6 : game->last_alive + 1;
		wattron(info, COLOR_PAIR(color));
		mvwprintw(info, n += 2, 2, "Winner: Player #%d, %s\n", 
				champs[game->last_alive - 1].num, 
				champs[game->last_alive - 1].name);
		wattroff(info, COLOR_PAIR(color));
	}
	box(info, 0, 0);
	wrefresh(info);
}

void		draw(t_game_info *game)
{
	set_field(game->visual.win_field, *(game->orig_cursor_list),
			game->visual.mem, game->color_mem);
	set_info(game->visual.win_info, game, game->visual.champs);
}
