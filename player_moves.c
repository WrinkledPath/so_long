#include "so_long.h"

static void		win_game(t_map **map, t_game **game);
static void		handle_movement(t_game *game, char dest, int y, int x, int new_y, int new_x);

void		move_player(t_game *game, int yx[2], int dy, int dx)
{
	int		new_x;
	int		new_y;
	int		y;
	int		x;
	char	dest;

	if (!game || !game->map)
		return ;
	y = yx[0];
	x = yx[1];
	new_y = yx[0] + dy;
	new_x = yx[1] + dx;
	dest = game->map->grid[new_y][new_x];
	if (dest == '1')
		return ;
	else if (dest == 'E' || dest == 'F')
	{
		if (game->collected == game->map->collectibles)
		{
			win_game(&(game->map), &game);
			return ;
		}
	}
	handle_movement(game, dest, y, x, new_y, new_x);
	load_map(&game);
}

static void		handle_movement(t_game *game, char dest, int y, int x, int new_y, int new_x)
{
	if (!game)
		return ;
	if (game->map->grid[y][x] == 'F')
		game->map->grid[y][x] = 'E';
	else
		game->map->grid[y][x] = '0';
	if (dest == 'E')
		game->map->grid[new_y][new_x] = 'F';
	else if (dest == 'C')
	{
		game->collected++;
		game->map->grid[new_y][new_x] = 'P';
	}
	else
		game->map->grid[new_y][new_x] = 'P';
}

static void		win_game(t_map **map, t_game **game)
{
	write(1, "YOU WIN!\n", 9);
	free_game(map, game);
	exit (0);
}
