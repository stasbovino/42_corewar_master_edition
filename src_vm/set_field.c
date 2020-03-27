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

static void set_separator(WINDOW *field, int *x, int *y, int width)
{
	if (*x + 3 < width - 1)
		{
			mvwprintw(field, *y, *x, " ");
			*x += 1;
		}
		else
		{
			mvwprintw(field, *y, *x, "\n");
			(*y)++;
			*x = 1;
		}
}

static void set_vars(int *width, int *x, int *y, int *i)
{
	*width = 194;
	*x = 1;
	*y = 1;
	*i = 0;
}

static int	set_color(t_cursor *cursor, int i, unsigned char *color_mem)
{
	int color;

	if (cursor && (color = is_cur_pos(cursor, i)))
		color = (color >= 6) ? 6 : color;
	else if (color_mem[i] != 0)
		color = (color_mem[i] >= 6) ? 16 : color_mem[i] + 11;
	else
		color = 20;
	return (color);
}

void		set_field(WINDOW *field, t_cursor *cursor, unsigned char *mem,
		unsigned char *color_mem)
{
	int y;
	int x;
	int i;
	int width;
	int color;

	werase(field);
	set_vars(&width, &x, &y, &i);
	while (i < MEM_SIZE)
	{
		color = set_color(cursor, i, color_mem);
		if (x + 2 < width - 1)
		{
				wattron(field, COLOR_PAIR(color));
			mvwprintw(field, y, x, "%.2hhx", mem[i]);
			wattroff(field, COLOR_PAIR(color));
			i++;
			x+=2;
		}
		set_separator(field, &x, &y, width);
	}
	box(field, 0, 0);
	wrefresh(field);
}
