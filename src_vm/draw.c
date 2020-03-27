#include "corewar.h"

void		draw(t_game_info *game)
{
	set_field(game->visual.win_field, *(game->orig_cursor_list),
			game->visual.mem, game->color_mem);
	set_info(game->visual.win_info, game, game->visual.champs);
}
