# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: peer <peer@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/13 21:19:23 by peer          #+#    #+#                  #
#    Updated: 2020/04/16 15:44:37 by Wester        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./src
GNL_DIR = ./gnl
PRINTF_DIR = ./ft_printf

SRC = 	minishell.c \
		directories.c \
		environment.c \
		bubblesort.c \
		utils.c \
		unset_env.c 
		
		
GNL = get_next_line.c get_next_line_utils.c

FILES = $(addprefix $(SRC_DIR)/, $(SRC))
FILES += $(addprefix $(GNL_DIR)/, $(GNL))
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