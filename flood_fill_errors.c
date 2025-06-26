#include "so_long.h"

static void convert_list_array(m_list *stack, t_map **map);
static char **clone_grid(t_map *map);
static void	flood_fill(int y, int x, char **grid, int width, int height);
static int path_error(char **grid);

int		validate_map_path(m_list **stack, t_map **map)
{
	int yx[2];
	char **clone;

	if ((init_map_grid(map, stack)) < 0)
		return (-1);
	convert_list_array(*stack, map);
	find_player(*map, yx);
	if (!(clone = clone_grid(*map)))
		return (confirmed_grid_error(map));
	flood_fill(yx[0], yx[1], clone, (*map)->width, (*map)->height);
	if (path_error(clone))
	{
		free_grid(clone);
		return (confirmed_grid_error(map));
	}
	return (0);
}

static void	convert_list_array(m_list *stack, t_map **map)
{
	int len;
	int i;
	int j;

	if (!stack)
		return ;
	i = 0;
	j = 0;
	len = (*map)->height;
	while (len--)
	{
		i = 0;
		while (stack->line[i])
		{
			(*map)->grid[j][i] = stack->line[i];
			i++;
		}
		(*map)->grid[j][i] = '\0';
		stack = stack->next;
		j++;
	}
	(*map)->grid[j] = NULL;
}

void find_player(t_map *map, int yx[2])
{
	int x;
	int y;

	y = 0;
	while(y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'P' || map->grid[y][x] == 'F')
			{
				yx[0] = y;
				yx[1] =	x;
				return ;
			}
			x++;
		}
		y++;
	}
	yx[0] = -1;
	yx[1] = -1;
}

static char **clone_grid(t_map *map)
{
	int i;
	char **clone;

	clone = malloc((map->height + 1) * sizeof(char *));
	if (!clone)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		if (!(clone[i] = ft_strdup(map->grid[i])))
		{
			while (i--)
				free(clone[i]);
			return (NULL);
		}
		i++;
	}
	clone[i] = NULL;
	return (clone);

}

static void	flood_fill(int y, int x, char **grid, int width, int height)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
		return;	
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	else
		grid[y][x] = 'V';

	flood_fill(y + 1, x, grid, width, height);
	flood_fill(y - 1, x, grid, width, height);
	flood_fill(y, x + 1, grid, width, height);
	flood_fill(y, x - 1, grid, width, height);
}

static int path_error(char **grid)
{
	int x;
	int y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'P' || grid[y][x] == 'E' || grid[y][x] == 'C')
			{
				write(1, "[ERROR]: Map Layout Incorrect\n", 30);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
