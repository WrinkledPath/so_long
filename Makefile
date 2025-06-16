# Project name
NAME = so_long

# Source files
SRC = mlx_test.c
OBJ = $(SRC:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Paths to libraries and includes
LIBFT_DIR = ./local_includes/Libft/
MINI_MLX_D = ./local_includes/minilibx-linux/

INCLUDES = -I. -I$(LIBFT_DIR) -I$(MINI_MLX_D)

# Full library paths
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MINI_MLX_D)/libmlx_Linux.a

# Default target
all: $(NAME)

# Linking final executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) \
		-L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

# Compiling object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

