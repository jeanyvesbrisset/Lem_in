# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrisset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/27 16:01:54 by jbrisset          #+#    #+#              #
#    Updated: 2019/07/04 13:53:19 by jbrisset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in

HEADER	= lem_in.h

SRC		= src/bfs_util.c\
		  src/bfs.c\
		  src/edmund_karp.c\
		  src/edkarp_util.c\
		  src/set_flow.c\
		  src/set_flow_util.c\
		  src/free_functions.c\
		  src/getters.c\
		  src/handle_ants.c\
		  src/handle_ants_util.c\
		  src/lem_in.c\
		  src/manage_visited.c\
		  src/parse_edge.c\
		  src/parse_room.c\
		  src/parsing.c\
		  src/map.c\
		  src/paths_manager.c\
		  src/queue_util.c\
		  src/index_data.c\

OBJ		= $(SRC:.c=.o)

LIB = libft/libftprintf.a

GCC = gcc

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

allclean: all clean

$(NAME): $(OBJ) $(LIB) $(PRINTF) $(SRC) $(LIB)
	@$(CC) $(FLAGS) -I $(HEADER) $(SRC) $(LIB) $(PRINTF) -o $(NAME)
	@printf "\n\033[032mLem-in Compilation OK \033[0m\n"
	@printf "\n\033[032m \"lem-in\" executable has been created\033[0m\n"

$(LIB):
	@make -C libft

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@printf "\n\033[032mObject files have been deleted\033[0m\n"

fclean:
	@make fclean -C libft
	@rm -f $(NAME) $(OBJ)
	@printf "\n\033[032m\"lem-in\" and object files have been deleted\033[0m\n"

re: fclean all

norme:
	norminette $(SRC)
	norminette $(HEADER)

.PHONY : all clean fclean re
