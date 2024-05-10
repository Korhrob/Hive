CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

OBJ		=	ft_printf.o ft_print_chr.o ft_print_str.o \
			ft_print_nbr.o ft_print_hex.o ft_print_ptr.o \
			ft_bonus.o ft_util.o

NAME	=	libftprintf.a

all: $(NAME)

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: make $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

test: $(NAME)
	cc $(CFLAGS) -o a main.c $(NAME)

.PHONY : all bonus clean fclean re test bonus
