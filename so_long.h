
#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_map {
	char **grid;
	int	players;
	int	collectibles;
	int	exits;
	int width;
	int height;
} t_map;

typedef struct	s_list {
	struct		s_list *prev;
	int			index;
	char		*line;
	struct		s_list *next;
} m_list;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*player_img;
	void	*wall_img;
	void	*exit_img;
	void	*floor_img;
	void	*coll_img;
	void	*player_exit;
	int		collected;
	int		image_width;
	int		image_height;
} t_game;

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"

#define PIXEL_SIZE 64

// Stack Utils
int		stack_len(m_list *stack);
int		append_node(m_list **stack, char *str);
void	set_index(m_list *stack);
int		free_stack(m_list **stack);
int		init_stack(m_list **stack, char *file);
m_list	*find_last_line(m_list *stack);

// Map Utils
int		handle_map_errors(m_list **stack, t_map **map);
int		validate_map_path(m_list **stack, t_map **map);
int		init_map_grid(t_map **map, m_list **stack);
int		free_grid(char **grid);
int		confirmed_grid_error(t_map **map);
void	confirmed_map_error(m_list **stack, t_map **map, int error);

// Window Utils

int		free_game(t_map **map, t_game **game);
int		init_window(t_map **map, t_game **game);
int		handle_close(void *param);
void	load_map(t_game **game);
int		render_loop(t_game *game);
void	find_player(t_map *map, int yx[2]);
int		handle_key(int keycode, void *param);

// Player Movement
void		move_player(t_game *game, int yx[2], int dy, int dx);

// Testing Utils
void	print_list(m_list *stack);

#endif
