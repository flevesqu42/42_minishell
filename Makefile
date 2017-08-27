# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 00:33:10 by flevesqu          #+#    #+#              #
#    Updated: 2017/08/27 06:30:13 by flevesqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RM = rm -f

LIB = libft

LIB_FLAG = 

ifdef ELECTRIC_MEMORY
	LIB_FLAG += ELECTRIC_MEMORY=1
endif

FILES =	main.c\
		builtin_env.c\
		builtin_cd.c\
		builtin_setenv.c\
		builtin_unsetenv.c\
		builtin_echo.c\
		is_a_builtin.c\
		is_a_bin.c\
		is_an_exec.c\
		selection.c\
		selection_loop.c\
		selection_colors.c\
		selection_move_index.c\
		selection_inputs.c\
		selection_display.c\
		autocomplete.c\
		autocomplete_actions.c\
		autocomplete_bufcmp.c\
		autocomplete_parse_word.c\
		cursor.c\
		cursor_inputs.c\
		signal_handler.c\
		signal_status.c\
		init_shell.c\
		shell_loop.c\
		line_loop.c\
		line_edit.c\
		prompt.c\
		exit_shell.c\
		errors.c\
		replace_line_buf.c\
		parse_chars.c\
		do_command.c\
		new_file_from_dirent.c\
		inputs.c\
		get_command_from_line.c\
		env_actions.c\
		get_path.c\
		relative_to_absolute_path.c\
		execute_command.c\
		get_working_directory.c\
		line_treatment.c\
		termcaps.c\

CC = clang

WFLAGS = -Wall -Werror -Wextra

ifdef DEBUG
	WFLAGS += -DDEBUGTTY="$(DEBUG)"
endif

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
	make -C $(LIB) $(LIB_FLAG)

obj/%.o: src/%.c $(HEADER)
	$(CC) -c $(WFLAGS) -I $(LIB_INCLUDES) -I $(SRC_INCLUDES) $< -o $@

$(NAME) : $(OBJ) $(HEADER)
	make -C $(LIB) $(LIB_FLAG)
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(LFLAGS)

clean : lclean
	$(RM) $(OBJ)
	$(RM) -d $(OBJ_DIR)

lclean :
	make -C $(LIB)/ clean

fclean : lfclean clean
	$(RM) $(NAME)

lfclean :
	make -C $(LIB)/ fclean

re : fclean all

lre :
	make -C $(LIB)/ re

.PHONY: all clean fclean re lclean lfclean lre
