#include "so_long.h"

void	load_map(t_game **game)
{
	int i;
	int j;
	char **curr;

	curr = (*game)->map->grid;
	j = 0;
	while (curr[j])
	{
		i = 0;
		while (curr[j][i])
		{
			if (curr[j][i] == '1')
				mlx_put_image_to_window((*game)->mlx, (*game)->win, \
						(*game)->wall_img, i * PIXEL_SIZE, j * PIXEL_SIZE);
			else if (curr[j][i] == '0')
				mlx_put_image_to_window((*game)->mlx, (*game)->win, \
						(*game)->floor_img, i * PIXEL_SIZE, j * PIXEL_SIZE);
			else if (curr[j][i] == 'P')
				mlx_put_image_to_window((*game)->mlx, (*game)->win, \
						(*game)->player_img, i * PIXEL_SIZE, j * PIXEL_SIZE);
			else if (curr[j][i] == 'C')
				mlx_put_image_to_window((*game)->mlx, (*game)->win, \
						(*game)->coll_img, i * PIXEL_SIZE, j * PIXEL_SIZE);
			else if (curr[j][i] == 'E')
				mlx_put_image_to_window((*game)->mlx, (*game)->win, \
						(*game)->exit_img, i * PIXEL_SIZE, j * PIXEL_SIZE);
			else if (curr[j][i] == 'F')
				mlx_put_image_to_window((*game)->mlx, (*game)->win, \
							(*game)->player_exit, i * PIXEL_SIZE, j * PIXEL_SIZE);
			i++;	
		}
		j++;
	}
}

int		handle_key(int keycode, void *param)
{
	t_game	*game;
	int		yx[2];

	game = (t_game *)param;
	find_player(game->map, yx);
	if (keycode == 65307)
	{
		free_game((&(game->map)), &game);
		exit (0);
	}
	if (keycode == 'W' || keycode == 'w')
		move_player(game, yx, -1, 0);
	else if (keycode == 'S' || keycode == 's')
		move_player(game, yx, +1, 0);
	else if (keycode == 'D' || keycode == 'd')
		move_player(game, yx, 0, +1);
	else if (keycode == 'A' || keycode == 'a')
		move_player(game, yx, 0, -1);
	return (0);
}
