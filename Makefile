NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra #-fsanitize=address -g3 -Werror
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
	  dist_cal.c\
	  utils.c\
	  move.c\
	  move2.c\
	  ray_cast.c\

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
