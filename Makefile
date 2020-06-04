# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: peer <peer@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/13 21:19:23 by peer          #+#    #+#                  #
#    Updated: 2020/06/04 16:43:55 by pde-bakk      ########   odam.nl          #
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
	@echo "$(BLUE)Remaking libft.a"
	@make re -C ./libft
	@cp ./libft/libft.a .
	@gcc $(FLAGS) -I ./include/ $(FILES) libft.a -o $(NAME)

clean:
	/bin/rm -f *.o *~ *.gch
	@make clean -C ./libft

fclean: clean
	@make fclean -C ./libft
	/bin/rm -f libft.a
	/bin/rm -f minishell

re: fclean all