# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: peer <peer@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/13 21:19:23 by peer          #+#    #+#                  #
#    Updated: 2020/06/12 17:42:52 by wbarendr      ########   odam.nl          #
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
		pipes.c

FILES = $(addprefix $(SRC_DIR)/, $(SRC))
#FILES += $(addprefix $(LIBFT_DIR), $(LIBFT))

FLAGS = -Wall -Werror -Wextra

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

re: fclean all