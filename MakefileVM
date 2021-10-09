NAME = minishell

MIN = libmini.a

MIND = ./lib/

GNLD = ./fcts/GNL/

LIBFT = libft.a

LIBFTD = ./fcts//libft/

COMPILE = gcc

CFLAGS = -Werror -Wextra -Wall $(COMPILE1)

SRCD = ./srcs/

SRCPARSING = parsing_files/

SRCBUILTIN = builtin/

SRCEXEC = exec_files/


SRC =	$(GNLD)get_next_line.c							\
		$(GNLD)get_next_line_utils.c					\
		$(SRCD)$(SRCPARSING)print_functions.c			\
		$(SRCD)$(SRCPARSING)sig_handler.c				\
		$(SRCD)$(SRCPARSING)type_functions.c			\
		$(SRCD)$(SRCPARSING)search_functions.c			\
		$(SRCD)$(SRCPARSING)fast_functions.c			\
		$(SRCD)$(SRCPARSING)parse_is_command.c			\
		$(SRCD)$(SRCPARSING)start_functions.c			\
		$(SRCD)$(SRCPARSING)parser_input.c				\
		$(SRCD)$(SRCPARSING)parser_output.c				\
		$(SRCD)$(SRCPARSING)lexer_start.c				\
		$(SRCD)$(SRCPARSING)free_functions.c			\
		$(SRCD)$(SRCBUILTIN)ft_menu.c					\
		$(SRCD)$(SRCBUILTIN)ft_echo.c					\
		$(SRCD)$(SRCPARSING)tree_input.c				\
		$(SRCD)$(SRCPARSING)tree_define.c				\
		$(SRCD)$(SRCPARSING)tree_output.c 				\
		$(SRCD)$(SRCPARSING)free_functions.c			\
		$(SRCD)$(SRCEXEC)full_functions.c				\
		$(SRCD)$(SRCEXEC)exec_input.c					\
		$(SRCD)$(SRCEXEC)exec_com.c						\
		$(SRCD)$(SRCEXEC)init_pip.c						\
		$(SRCD)$(SRCEXEC)exec_fast_functions.c			\
		$(SRCD)$(SRCEXEC)exec_waiter.c					\
		$(SRCD)$(SRCEXEC)exec_redirections.c			\
		$(SRCD)$(SRCEXEC)exec_heredoc.c					\
		$(SRCD)$(SRCEXEC)exec_pipe.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(COMPILE) $(CFLAGS) -c $< -L/usr/include -lreadline -o $@

all: $(NAME)

$(NAME) : $(OBJ) $(SRCD)/main.c
		rm -rf $(NAME)
		make -C $(LIBFTD)
		cp $(LIBFTD)$(LIBFT) $(MIND)$(MIN)
		ar rc $(MIND)$(MIN) $(OBJ)
		rm -f $(LIBFT)
		ranlib $(MIND)$(MIN)
		$(COMPILE) $(CFLAGS) -o $(NAME) $(COMPILE2) $(SRCD)/main.c  $(MIND)$(MIN) -L/usr/include -lreadline

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
