NAME = minishell

MIN = libmini.a

MIND = ./lib/

GNLD = ./fcts/GNL/

LIBFT = libft.a

LIBFTD = ./fcts//libft/

COMPILE = gcc

CFLAGS = -Werror -Wextra -Wall -g $(COMPILE1)

SRCD = ./srcs/

SRCPARSING = parsing_files/

SRCBUILTIN = builtin/

SRCEXEC = exec_files/

SRCENV = env/

SRC =	$(GNLD)get_next_line.c							\
		$(GNLD)get_next_line_utils.c					\
		$(SRCD)$(SRCPARSING)arg_gestion.c				\
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
		$(SRCD)$(SRCPARSING)tree_input.c				\
		$(SRCD)$(SRCPARSING)tree_define.c				\
		$(SRCD)$(SRCPARSING)free_functions.c			\
		$(SRCD)$(SRCPARSING)small_free_functions.c		\
		$(SRCD)$(SRCEXEC)full_functions.c				\
		$(SRCD)$(SRCEXEC)exec_input.c					\
		$(SRCD)$(SRCEXEC)exec_com.c						\
		$(SRCD)$(SRCEXEC)functions_arg.c				\
		$(SRCD)$(SRCEXEC)init_pip.c						\
		$(SRCD)$(SRCEXEC)exec_fast_functions.c			\
		$(SRCD)$(SRCEXEC)exec_waiter.c					\
		$(SRCD)$(SRCEXEC)exec_redirections.c			\
		$(SRCD)$(SRCEXEC)exec_heredoc.c					\
		$(SRCD)$(SRCEXEC)exec_pipe.c					\
		$(SRCD)$(SRCENV)delete_variable.c				\
		$(SRCD)$(SRCENV)environment.c					\
		$(SRCD)$(SRCENV)init_env.c						\
		$(SRCD)$(SRCENV)utils_env.c						\
		$(SRCD)$(SRCBUILTIN)ft_cd.c						\
		$(SRCD)$(SRCBUILTIN)cd_utils.c					\
		$(SRCD)$(SRCBUILTIN)ft_pwd.c					\
		$(SRCD)$(SRCBUILTIN)ft_echo.c					\
		$(SRCD)$(SRCBUILTIN)ft_unset.c					\
		$(SRCD)$(SRCBUILTIN)ft_env.c					\
		$(SRCD)$(SRCBUILTIN)ft_export.c					\
		$(SRCD)$(SRCBUILTIN)menu.c

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
