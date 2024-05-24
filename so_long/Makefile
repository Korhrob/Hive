CC			=	cc
FLAGS		=	-Wall -Werror -Wextra
NAME		=	so_long
SRC			=	main.c list.c entity.c map.c map_parser.c \
				game.c game_events.c render.c resources.c flood_fill.c
OBJ			=	$(SRC:.c=.o)
MLX			=	MLX42
MLX_FOLDER	=	$(MLX)/build
MLX_LIB		=	$(MLX_FOLDER)/libmlx42.a
INC			=	-Iinclude -lglfw -L"/Users/rkorhone/.brew/opt/glfw/lib/"
LIBFT		=	libft
LIBFT_LIB	=	$(LIBFT)/libft.a

all: install $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MLX_FOLDER)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(INC)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean
	rm -rf $(MLX_FOLDER)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: clean all

install: $(MLX_FOLDER)

$(MLX_FOLDER):
	cmake $(MLX) -B $(MLX_FOLDER)

.PHONY: all clean fclean re install