NAME = cub3d
CC = gcc
CFLAGS = -Wall #-fsanitize=address -g3 #-Wextra -Werror
FLAGS = -Lmlx_linux -lmlx_Linux -L./minilibx-linux/ -Imlx_linux -lXext -lX11 -lm -lz

SRC = main.c \
      parse_map.c \
      get_next_line.c \
      get_next_line_utils.c \
      parsing.c \
	  image.c\
	  distance_calculation.c\

OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) $(FLAGS) -o $(NAME)
	@echo "Cub3D is ready!"

$(LIBFT):
	@make -C libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
