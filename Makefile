NAME = minishell

MIN = libmini.a

MIND = ./lib/

SRCD = ./srcs/

COMPILE = gcc

CFLAGS = -pthread -Wall -Wextra -Werror

SRC =	$(SRCD)

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		ar rc $(MIND)$(MIN) $(OBJ)
		ranlib $(MIND)$(MIN)
		$(COMPILE) $(CFLAGS) -o $(NAME) $(SRCD)/main.c  $(MIND)$(MIN)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MIND)$(MIN)

re: fclean all

.PHONY: clean fclean all re
