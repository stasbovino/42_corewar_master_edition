#include "corewar.h"

static void	init_colors(void)
{
	init_color(COLOR_CYAN, 128, 128, 128);

	init_pair(1, COLOR_WHITE, COLOR_BLACK);

	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);

	init_pair(8, COLOR_RED, COLOR_BLACK);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);

	init_pair(12, COLOR_RED, COLOR_BLACK);
	init_pair(13, COLOR_GREEN, COLOR_BLACK);
	init_pair(14, COLOR_YELLOW, COLOR_BLACK);
	init_pair(15, COLOR_BLUE, COLOR_BLACK);
	init_pair(16, COLOR_MAGENTA, COLOR_BLACK);

	init_pair(20, COLOR_CYAN, COLOR_BLACK);
}

static void	bad_term()
{
	ft_printf("bad terminal size. Rescale, or disable visualisation.\n");
	exit(1);
}

void		init_ncurses(t_ncurses *visual, t_game_info *game,
		unsigned char *mem, t_cursor **cursor_list)
{
	int height;
	int width;
	int space;

	initscr();
	if (COLS < 40)
		bad_term();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	start_color();
	init_colors();
	height = LINES;
	width = 194;
	space = 192 * (LINES - 2);
	if (space < MEM_SIZE)
		bad_term();
	visual->win_field = newwin(height, width, 0, 10);
	visual->win_info = newwin(LINES, 50, 0, width + 12);
}
