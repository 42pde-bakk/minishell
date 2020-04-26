# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: peer <peer@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/13 21:19:23 by peer          #+#    #+#                  #
#    Updated: 2020/04/26 17:57:17 by peer          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./src
PRINTF_DIR = ./ft_printf

SRC = 	minishell.c \
		directories.c \
		environment.c \
		bubblesort.c \
		utils.c \
		unset_env.c \
		split_quotes.c \
		get_next_line_q.c \
		ft_strstrip.c
		

FILES = $(addprefix $(SRC_DIR)/, $(SRC))
#FILES += $(addprefix $(LIBFT_DIR), $(LIBFT))

all: $(NAME)

$(NAME): $(FILES)
	@echo "$(BLUE)Remaking libft.a"
	@make re -C ./libft
	@cp ./libft/libft.a .
	@gcc $(FLAGS) -I ./include/ $(FILES) libft.a -o $(NAME)

clean:
	/bin/rm -f *.o *~ *,gch

fclean: clean
	@make fclean -C ./libft
	/bin/rm -f libft.a
	/bin/rm -f minishell

re: fclean all