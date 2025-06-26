#include "so_long.h"

static void		calculate_win_size(t_map *map, int win_size[2]);
static void		free_images(t_game **game);
static int		load_images(t_map **map, t_game **game);
static int		check_sizes(t_game **game, int image_width, int image_height);
static int	iterate_sizes(int widths[5], int heights[5], int image_width, int image_height);

int		init_window(t_map **map, t_game **game)
{
	int win_size[2];

	*game = malloc(sizeof(t_game));
	if (!(*game))
		return (free_game(map, game));
	if (!((*game)->mlx = mlx_init()))
		return(free_game(map, game));
	calculate_win_size(*map, win_size);
	if (!((*game)->win = mlx_new_window((*game)->mlx, win_size[0], \
					win_size[1], "Knight Kastle")))
		return(free_game(map, game));
	if (load_images(map, game) < 0)
		return (-1);
	mlx_loop_hook((*game)->mlx, render_loop, *game);
	mlx_hook((*game)->win, 2, 1L<<0, handle_key, *game);
	mlx_hook((*game)->win, 17, 0, handle_close, *game);
	mlx_loop((*game)->mlx);
	return (0);
}

int		handle_close(void *param)
{
	t_game *game = (t_game *)param;
	free_game(&(game->map), &game);
	exit (0);
}

int		render_loop(t_game *game)
{
	load_map(&game);
	return (0);
}
static int	load_images(t_map **map, t_game **game)
{
	int		image_width;
	int		image_height;

	(*game)->map = *map;
	(*game)->player_img = NULL;
	(*game)->wall_img = NULL;
	(*game)->exit_img = NULL;
	(*game)->floor_img = NULL;
	(*game)->coll_img = NULL;
	(*game)->player_exit = NULL;
	(*game)->collected = 0;
	(*game)->player_img = mlx_xpm_file_to_image((*game)->mlx, \
					"./Sprites/player.xpm", &image_width, &image_height);
	if (check_sizes(game, image_width, image_height) < 0)
		return (free_game(map, game));
	(*game)->image_width = image_width;
	(*game)->image_height = image_height;
	return (0);
}

static int		check_sizes(t_game **game, int image_width, int image_height)
{
	int		widths[5];
	int		heights[5];

	widths[5] = 0;
	heights[5] = 0;
	(*game)->wall_img = mlx_xpm_file_to_image((*game)->mlx,
					"./Sprites/wall.xpm", &widths[0], &heights[0]);
	(*game)->exit_img = mlx_xpm_file_to_image((*game)->mlx,
					"./Sprites/exit.xpm", &widths[1], &heights[1]);
	(*game)->floor_img = mlx_xpm_file_to_image((*game)->mlx,
					"./Sprites/floor.xpm", &widths[2], &heights[2]);
	(*game)->coll_img = mlx_xpm_file_to_image((*game)->mlx,
					"./Sprites/collectible_fruit_apple.xpm", &widths[3], &heights[3]);
	(*game)->player_exit = mlx_xpm_file_to_image((*game)->mlx, 
			"./Sprites/player_exit.xpm", &widths[4], & heights[4]);
	if (iterate_sizes(widths, heights, image_width, image_height) < 0)
		return (-1);
	return (0);
}

static int	iterate_sizes(int widths[5], int heights[5], int image_width, int image_height)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (widths[i++] != image_width)
			return(-1);
	}
	i = 0;
	while (i < 5)
	{
		if (heights[i++] != image_height)
			return (-1);
	}
	return (0);

}
static void calculate_win_size(t_map *map, int win_size[2])
{
	win_size[0] = map->width * PIXEL_SIZE;
	win_size[1] = map->height * PIXEL_SIZE;	
}

int		free_game(t_map **map, t_game **game)
{
	free_grid((*map)->grid);
	free_images(game);
	if ((*game)->win)
	{
		mlx_destroy_window((void *)(*game)->mlx, (void *)(*game)->win);		
		(*game)->win = NULL;
	}
	if ((*game)->mlx)
	{
		mlx_destroy_display((*game)->mlx);
		(*game)->mlx = NULL;
	}
	if (*game)
		free(*game);
	*game = NULL;
	free(*map);
	*map = NULL;
	return (-1);
}

static void		free_images(t_game **game)
{
	if ((*game)->player_img)
	{
		mlx_destroy_image((void *)(*game)->mlx, (void *)(*game)->player_img);
		(*game)->player_img = NULL;
	}
	if ((*game)->wall_img)
	{
		mlx_destroy_image((void *)(*game)->mlx, (void *)(*game)->wall_img);
		(*game)->wall_img = NULL;
	}
	if ((*game)->exit_img)
	{
		mlx_destroy_image((void *)(*game)->mlx, (void *)(*game)->exit_img);
		(*game)->exit_img = NULL;
	}
	if ((*game)->floor_img)
	{
		mlx_destroy_image((void *)(*game)->mlx, (void *)(*game)->floor_img);
		(*game)->floor_img = NULL;
	}
	if ((*game)->coll_img)
	{
		mlx_destroy_image((void *)(*game)->mlx, (void *)(*game)->coll_img);
		(*game)->coll_img = NULL;
	}
}
