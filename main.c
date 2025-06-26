#include "so_long.h"

static int	process_map(m_list **stack, t_map **map);
static int	check_file(char *file);

int	main (int argc, char **argv)
{
	m_list *stack_a;
	t_map *map;
	t_game *game;

	if (argc != 2 || !argv[1])
		return (-1);
	stack_a = NULL;
	map = NULL;
	game = NULL;
	if ((check_file(argv[1])) < 0)
		return (-1);
	if ((init_stack(&stack_a, argv[1])) != 0)
		return (free_stack(&stack_a));
	if ((process_map(&stack_a, &map)) < 0)
		return (-1);
	if ((init_window(&map, &game)) < 0)
		return (-2);
	printf("\n");
}

static int	check_file(char *file)
{
	char *correct;
	int	ext;
	int i;

	correct = ".ber";
	ext = ft_strlen(file) - 4;
	i = 0;
	while (file[ext + i])
	{
		if (file[ext + i] != correct[i])
			return (-1);
		i++;
	}
	return (0);
}
static int	process_map(m_list **stack, t_map **map)
{
	if ((handle_map_errors(stack, map)) < 0)
		return (-1);
	if ((validate_map_path(stack, map)) < 0)
		return (-1);
	free_stack(stack);
	return (0);
}

m_list	*find_last_line(m_list *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}
