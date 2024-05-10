CC		= cc
CFLAGS	= -Wall -Wextra -Werror
OBJ		=	ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
			ft_strlen.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o \
		   	ft_strchr.o ft_strrchr.o ft_strncmp.o ft_strnstr.o ft_memset.o \
			ft_memcpy.o ft_memmove.o ft_memchr.o ft_memcmp.o ft_calloc.o \
			ft_strdup.o ft_atoi.o ft_bzero.o ft_substr.o ft_strjoin.o \
			ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o \
			ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
BONUS	=	ft_lstnew_bonus.o ft_lstadd_front_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o ft_lstadd_back_bonus.o \
			ft_lstdelone_bonus.o ft_lstclear_bonus.o ft_lstiter_bonus.o ft_lstmap_bonus.o
NAME		= libft.a
PRINTF		= ft_printf
PRINTF_LIB	= ft_printf/libftprintf.a
TEMP		= .bonus

all: $(NAME)

$(NAME): $(OBJ) $(PRINTF_LIB)
	ar rcs $(NAME) $(OBJ) $(PRINTF_LIB)

$(TEMP): $(OBJ) $(BONUS)
	ar rcs $(NAME) $(OBJ) $(BONUS)
	touch $(TEMP)

bonus: $(TEMP)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF)

clean:
	rm -f $(OBJ) $(BONUS)
	$(MAKE) -C $(PRINTF) clean

fclean: clean
	rm -f $(NAME) $(TEMP)
	$(MAKE) -C $(PRINTF) fclean

re: fclean $(NAME)

.PHONY : all bonus clean fclean re
