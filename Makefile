# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: peer <peer@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/13 21:19:23 by peer          #+#    #+#                  #
#    Updated: 2020/06/17 16:24:59 by pde-bakk      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./src
PRINTF_DIR = ./ft_printf

SRC = 	minishell.c \
		directories.c \
		redirections.c \
		environment.c \
		bubblesort.c \
		utils.c \
		utils2.c \
		utils3.c \
		utils4.c \
		unset_env.c \
		split_quotes1.c \
		split_quotes2.c \
		get_next_line_q.c \
		ft_strstrip.c \
		execute.c \
		write_instant.c \
		export.c \
		free_functions.c \
		ft_split_q.c \
		gameloop.c \
		trimming.c \
		syntax.c \
		builtins_echo_exit.c

FILES = $(addprefix $(SRC_DIR)/, $(SRC))
#FILES += $(addprefix $(LIBFT_DIR), $(LIBFT))
# COLORS
PINK = \x1b[35;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m
RED = \x1b[31;01m
WHITE = \x1b[31;37m
RESET = \x1b[0m

FLAGS = -Wall -Werror -Wextra -g
ifdef DEBUG
 FLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(FILES)
	@echo "$(BLUE)Remaking libft.a and libftprintf.a"
	@make re -s -C ./libft
	@cp ./libft/libft.a .
	@make re -s -C ./ft_dprintf
	@cp ./ft_dprintf/libftprintf.a .
	@gcc $(FLAGS) -I ./include/ $(FILES) libft.a libftprintf.a -o $(NAME)

clean:
	/bin/rm -f *.o *~ *.gch
	@make clean -s -C ./libft
	@make clean -s -C ./ft_dprintf

fclean: clean
	@make fclean -s -C ./libft
	@make fclean -s -C ./ft_dprintf
	/bin/rm -f libft.a
	/bin/rm -f libftprintf.a
	/bin/rm -f minishell
	/bin/rm -rf minishell.dSYM

re: fclean all
