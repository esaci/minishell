NAME = minishell

MIN = libmini.a

MIND = ./lib/

GNLD = ./fcts/GNL/

LIBFT = libft.a

LIBFTD = ./fcts//libft/

SRCD = ./srcs/

COMPILE = gcc

CFLAGS = -Werror -Wextra -Wall $(COMPILE1)

COMPILE1 = -I /Users/$(USER)/.brew/opt/readline/include

COMPILE1U = -I /usr/include/readline

COMPILE2 = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

COMPILE2U = -lreadline -L /usr/include/readline

SRC =	$(GNLD)get_next_line.c				\
		$(GNLD)get_next_line_utils.c		\
		$(SRCD)print_functions.c			\
		$(SRCD)sig_handler.c				\
		$(SRCD)start_functions.c			\
		$(SRCD)custom_pipex.c				\
		$(SRCD)parser_input.c				\
		$(SRCD)lexer_start.c				\
		$(SRCD)free_functions.c				

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		make -C $(LIBFTD)
		cp $(LIBFTD)$(LIBFT) $(MIND)$(MIN)
		ar rc $(MIND)$(MIN) $(OBJ)
		rm -f $(LIBFT)
		ranlib $(MIND)$(MIN)
		$(COMPILE) $(CFLAGS) -o $(NAME) $(COMPILE2) $(SRCD)/main.c  $(MIND)$(MIN)

ub: $(NAME)
	$(OBJ) $(SRCD)/main.c
	rm -rf $(NAME)
	make -C $(LIBFTD)
	cp $(LIBFTD)$(LIBFT) $(MIND)$(MIN)
	ar rc $(MIND)$(MIN) $(OBJ)
	rm -f $(LIBFT)
	ranlib $(MIND)$(MIN)
	$(COMPILE) $(CFLAGS) -o $(NAME) $(COMPILE2U) $(SRCD)/main.c  $(MIND)$(MIN)


clean:
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFTD)
	rm -rf $(NAME)
	rm -rf $(MIND)$(MIN)

re: fclean all

.PHONY: clean fclean all re
