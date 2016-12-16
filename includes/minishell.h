/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:57:45 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/16 06:34:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <term.h>
# include <limits.h>

# define CMD_NOT_FOUND		1
# define CMD_TOO_LONG		2
# define READ_ERROR			3
# define CD_ERROR			4
# define FORK_ERROR			5
# define NO_FILE			6
# define NO_RIGHT			7
# define MALLOC_ERROR		8
# define ALNUM_ERROR		9
# define FIRST_LETTER_ERROR	10
# define IS_A_DIRECTORY		11
# define HOME_NOT_SET		12
# define GETATTR_ERROR		13
# define SETATTR_ERROR		14

# define QUOTES				0x7
# define DOUBLE_QUOTE			0x1
# define SIMPLE_QUOTE			0x2
# define BACKSLASH				0x4

typedef struct	s_sh
{
    unsigned long	flags;
	char			**env;
	char			*name;
	char			prompt[PATH_MAX + 17];
	struct termios	old_terms;
	struct termios	my_terms;
}				t_sh;

void			exit_shell(t_sh *sh);
void			sh_error(int err, char *command, char *vm);
void			push_to_env(char ***env, char *key, char *value);
void			is_an_exec(t_sh *sh, char **cmd, char *path);
void			treat_command(t_sh *sh, char **cmd);
void			treat_line(t_sh *sh, char *line);
void			env_built(t_sh *sh, char **cmd);
void			echo_built(char **cmd);
void			push_to_env(char ***env, char *key, char *value);
void			display_env(char **env);
void			new_env(char ***dst, char **src);
void			unset_env(char ***env, char *to_unset);
void			execute_command(t_sh *sh, char **cmd, char *path);
int				get_path(char **env_path, char *path);
int				check_in_directory(t_sh *sh, char **cmd, char *path);
void			set_env_built(t_sh *sh, char **cmd);
void			unset_env_built(t_sh *sh, char **cmd);
void			change_directory(t_sh *sh, char *arg);
int				is_a_bin(t_sh *sh, char **cmd);
int				is_a_builtin(t_sh *sh, char **cmd);
void			signal_handler(int i);

#endif
