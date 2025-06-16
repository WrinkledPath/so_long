#include "so_long.h"

static void	append_node(l_list **stack, char *str);
static l_list *find_last_line(l_list *stack);
static void	init_stack(l_list **stack);

int	main (void)
{
	l_list *stack_a;

	stack_a = NULL;
	init_stack(&stack_a);
	while (stack_a)
	{
		printf("%s", stack_a->line);
		stack_a = stack_a->next;
	}
}

static void	init_stack(l_list **stack)
{
	int fd;	
	char *curr;

	fd = open("./maps/map01.ber", O_RDONLY);
	while ((curr = get_next_line(fd)))
	{
		append_node(stack, curr);
	}
	close(fd);		
}

static void	append_node(l_list **stack, char *str)
{
	l_list *new_list;
	l_list *last;

	new_list = malloc(sizeof(l_list));
	if (!new_list)
		return ;
	new_list->next = NULL;
	new_list->line = str;
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
}

static l_list *find_last_line(l_list *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}
