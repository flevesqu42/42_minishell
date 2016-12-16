# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 00:33:10 by flevesqu          #+#    #+#              #
#    Updated: 2016/12/16 00:27:35 by flevesqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = libft

FILES =	main.c\
		built_env.c\
		env_actions.c\
		command_treatment.c\
		exec.c\
		builtins.c

CC = clang

WFLAGS = -Wall -Werror -Wextra -O3 -march=native -ffast-math

LFLAGS = -L $(LIB)/ -lft -lm  -ltermcap

LIB_INCLUDES = ./$(LIB)/includes/

SRC_INCLUDES = ./includes/

SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

HEADER = $(SRC_INCLUDES)$(NAME).h

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(LIB) :
	make -C $(LIB)

obj/%.o: src/%.c $(HEADER)
	$(CC) -c $(WFLAGS) -I $(LIB_INCLUDES) -I $(SRC_INCLUDES) $< -o $@

$(NAME) : $(OBJ) $(HEADER)
	make -C $(LIB)
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS)

clean : lclean
	rm -rf $(OBJ)
	@if test -d $(OBJ_DIR);then rmdir $(OBJ_DIR) && echo "directory "$(OBJ_DIR)" deleted.";fi

lclean :
	make -C $(LIB)/ clean

fclean : lfclean clean
	rm -f $(NAME)

lfclean :
	make -C $(LIB)/ fclean

re : fclean all

lre :
	make -C $(LIB)/ re

.PHONY: all clean fclean re lclean lfclean lre
