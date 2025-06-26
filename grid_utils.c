#include "so_long.h"

int	init_map_grid(t_map **map, m_list **stack)
{
	int i;
	
	(*map)->grid = ft_calloc(((*map)->height + 1), sizeof(char *));
	if (!(*map)->grid)
	{
		free_stack(stack);
		confirmed_map_error(stack, map, -1);
		return (-1);
	}
	i = 0;
	while (i < (*map)->height)
	{
		(*map)->grid[i] = ft_calloc((*map)->width, sizeof(char));
		if (!(*map)->grid[i])
		{
			free_stack(stack);
			return (confirmed_grid_error(map));
		}
		i++;
	}
	return (0);
}

int	confirmed_grid_error(t_map **map)
{
	free_grid((*map)->grid);
	free(*map);
	*map = NULL;
	return (-1);
}

int free_grid(char **grid)
{
	int i;
	
	if (!grid || !*grid)
		return (-1);
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	grid = NULL;
	return (-1);
}
