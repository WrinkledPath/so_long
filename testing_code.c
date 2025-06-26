#include "so_long.h"

void	print_list(m_list *stack)
{
	while (stack)
	{
		printf("--------------\n");
		printf("Prev : ");
		if (stack && stack->prev)
			printf("%i\n", stack->prev->index);
		else
			printf("--\n");
		printf("Index : %i\n", stack->index);
		printf("Line : %s\n", stack->line);
		printf("Next : ");
		if (stack && stack->next)
			printf("%i\n", stack->next->index);
		else
			printf("--\n");
		printf("--------------\n");
		stack = stack->next;
	}
}
