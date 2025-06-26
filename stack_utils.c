#include "so_long.h"

int	init_stack(m_list **stack, char *file)
{
	int fd;
	int	len;
	int	r_val;
	char *tmp;
	char *curr;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("open");
	while ((curr = get_next_line(fd)))
	{
		len = ft_strlen(curr);
		if (!(tmp = ft_substr(curr, 0, len - 1)))
			return (-1);
		if ((r_val = append_node(stack, tmp)) != 0)
			return (-1);;
		free(curr);
		free(tmp);
	}
	set_index(*stack);
	close(fd);	
	return (0);
}

int		append_node(m_list **stack, char *str)
{
	m_list *new_list;
	m_list *last;

	new_list = malloc(sizeof(m_list));
	if (!new_list || !str)
		return (-1);
	new_list->next = NULL;
	new_list->line = ft_strdup(str);
	if (stack && *stack)
	{
		last = find_last_line(*stack);
		new_list->prev = last;
		last->next = new_list;
	}
	else
	{
		new_list->prev = NULL;
		*stack = new_list;
	}
	return (0);
}

int	stack_len(m_list *stack)
{
	int count;

	count = 0;
	if (!stack)
		return (0);
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}

void	set_index(m_list *stack)
{
	int	i;
 
	if (!stack)
		return ;
	i = 0;
	while (stack)
	{
		stack->index = i;
		stack = stack->next;
		i++;
	}
}

int	free_stack(m_list **stack)
{
	m_list *curr;
	m_list *tmp;

	curr = *stack;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	return (-1);
}
