CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
LDFLAG		=	#-g -fsanitize=address
NAME		=	pipex
SRC			=	main.c pipex.c pipex_utils.c path.c
OBJ			=	$(SRC:.c=.o)
LIBFT		=	Libft
LIBFT_LIB	=	$(LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT_LIB) $(LDFLAG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: clean all

.PHONY: all clean fclean re