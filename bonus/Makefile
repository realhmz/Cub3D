NAME = cub3d
CC = cc
CFLAGS = -Wall #-fsanitize=address -g3 #-Wextra -Werror
FLAGS = -Lmlx_linux -lmlx_Linux -L./minilibx-linux/ -Imlx_linux -lXext -lX11 -lm -lz

SRC = main.c \
    parse_map.c \
    get_next_line.c \
    get_next_line_utils.c \
    parsing.c \
	parsing1.c \
	parsing2.c \
	parsing3.c \
	image.c\
	distance_calculation.c\
	animation.c\
	ray_cast.c\
	utils.c\
	mini_map.c\
	mini_map2.c\
	line.c\

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
