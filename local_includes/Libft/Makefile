# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I. -g
CFLAGS += -I/usr/lib/modules/6.1.52-valve16-1-neptune-61/build/include/uapi \
          -I/usr/lib/modules/6.1.52-valve16-1-neptune-61/build/include

# Source and object files
SRCS    = src/ft_atol.c src/ft_isprint.c src/ft_putchar_fd.c src/ft_striteri.c src/ft_strnstr.c \
          src/ft_bzero.c src/ft_itoa.c src/ft_putendl_fd.c src/ft_strjoin.c src/ft_strrchr.c \
          src/ft_calloc.c src/ft_memchr.c src/ft_putnbr_fd.c src/ft_strlcat.c src/ft_strtrim.c \
          src/ft_isalnum.c src/ft_memcmp.c src/ft_putstr_fd.c src/ft_strlcpy.c src/ft_substr.c \
          src/ft_isalpha.c src/ft_memcpy.c src/ft_split.c src/ft_strlen.c src/ft_tolower.c \
          src/ft_isascii.c src/ft_memmove.c src/ft_strchr.c src/ft_strmapi.c src/ft_toupper.c \
          src/ft_isdigit.c src/ft_memset.c src/ft_strdup.c src/ft_strncmp.c

OBJS    = $(SRCS:.c=.o)
NAME    = libft.a

# Default target
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# Clean object files
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)

# Clean all build files
fclean: clean
	@echo "Removing library..."
	@rm -f $(NAME)

# Rebuild everything
re: fclean all
	@echo "Rebuilding..."

.PHONY: all clean fclean re

