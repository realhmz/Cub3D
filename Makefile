
all :
	cc *.c -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -fsanitize=address -g3 -lm -lz -o cub3d