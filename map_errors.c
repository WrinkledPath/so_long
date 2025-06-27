#include "so_long.h"

static int	errors_miscelaneous(t_map *map);
static int	same_size(m_list *stack, t_map *map);
static int	init_map_info(m_list **stack, t_map **map);
static int	error_walls(char *line, int row, int col, int height);
static int	add_miscelaneous(t_map *map, char c);
static int	iterate_line(m_list *stack, t_map *map);
static int	return_with_cleanup(int err, m_list **stack, t_map **map);

int		handle_map_errors(m_list **stack, t_map **map)
{
	int		j;
	int		r_val;
	m_list	*curr;

	j = 0;
	r_val = init_map_info(stack, map);
	if (r_val == -1)
		return (-1);
	curr = *stack;
	while (curr)
	{
		if ((r_val = iterate_line(curr, *map)) < 0)
			return (return_with_cleanup(r_val, stack, map));
		if ((r_val = same_size(curr, *map)) < 0)
			return (return_with_cleanup(r_val, stack, map));
		j++;
		curr = curr->next;
	}
	if ((r_val = errors_miscelaneous(*map)) < 0)
		return (return_with_cleanup(r_val, stack, map));
	return (0);
}

static int	same_size(m_list *curr, t_map *map)
{
	if ((int)ft_strlen(curr->line) == map->width)
		return (0);
	return (-3);
}

static int	iterate_line(m_list *node, t_map *map)
{
	int		i;
	int		r_val_wall;
	int		r_val_misc;
	
	i = 0;
	while (node->line[i])
	{
		r_val_wall = error_walls(node->line, node->index, i, map->height);
		r_val_misc = add_miscelaneous(map, node->line[i]);
		if (r_val_wall < 0 || r_val_misc < 0)
			break;
		i++;
	}
	if (r_val_wall < 0)
		return (r_val_wall);
	if (r_val_misc < 0)
		return (r_val_misc);
	else
		return (0);
}
static int init_map_info(m_list **stack, t_map **map)
{
	(*map) = malloc(sizeof(t_map));
	if (!*map)
	{
		confirmed_map_error(stack, map, -1);
		return (-1);
	}
	(*map)->players = 0;
	(*map)->collectibles = 0;
	(*map)->exits = 0;
	(*map)->height = stack_len(*stack);
	(*map)->width = ft_strlen((*stack)->line);
	(*map)->grid = NULL;
	return (1);
}

static int	error_walls(char *line, int row, int col, int height)
{
	int len;

	len = ft_strlen(line);
	if ((row == 0 ||
	   row == height - 1 || 
	   col == 0 || 
	   col == len - 1) && 
	   line[col] != '1' && line[col] != 'E')
		return (-2);
	else
		return (0);
}

static int	add_miscelaneous(t_map *map, char c)
{
	if (c == 'E')
		map->exits++;
	else if (c == 'C')
		map->collectibles++;
	else if (c == 'P')
		map->players++;
	else if (c != '1' && c != '0')
		return (-7);
	return (0);
}

static int	errors_miscelaneous(t_map *map)
{
	if (map->players != 1)
		return (-4);
	if (map->collectibles < 1)
		return (-5);
	if (map->exits != 1)
		return (-6);
	if (map->height > 16 || map->width > 30)
		return (-8);
	return (0);
}

void confirmed_map_error(m_list **stack, t_map **map, int error)
{
	if (error == -1)
		write(1, "[ERROR]:Failed malloc\n", 22);
	else if (error == -2)
		write(1, "[ERROR]:Map not surrounded by walls\n", 35);
	else if (error == -3)
		write(1, "[ERROR]:Uneven Map Lines\n", 25);
	else if (error == -4)
		write(1, "[ERROR]:Not 1 Player\n", 21);
	else if (error == -5)
		write(1, "[ERROR]:Missing Collectibles\n", 29);
	else if (error == -6)
		write(1, "[ERROR]:Not 1 Exit\n,", 19);
	else if (error == -7)
		write(1, "[ERROR]:Non Admitted Char in map\n", 33);
	else if (error == -8)
		write(1, "[ERROR]:Map Too Big (Min: 4x3 / Max: 16x30)\n", 44);
	free_stack(stack);
	free(*map);
	*map = NULL;
}

static int	return_with_cleanup(int err, m_list **stack, t_map **map)
{
	confirmed_map_error(stack, map, err);
	return (err);
}
