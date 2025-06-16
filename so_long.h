
#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_list {
	struct s_list *prev;
	char *line;
	struct s_list *next;
} l_list;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"

#endif
