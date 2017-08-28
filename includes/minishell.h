/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:57:45 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 08:35:52 by flevesqu         ###   ########.fr       */
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

/*
** debug preprocessor, use with this argument on make :
** DEBUG=["tty_name"] (example: `make re DEBUG=\\\"/dev/ttys001\\\"`)
** else the dprintf will not appear in binary
*/

# ifdef DEBUGTTY

int	g_debug_fd;

#  define DEBUG_INIT()	g_debug_fd = open(DEBUGTTY, O_WRONLY)
#  define DEBUG(...)	dprintf(g_debug_fd, __VA_ARGS__)

# else

#  define DEBUG_INIT()
#  define DEBUG(...)

# endif

/*
** shell structure
*/

typedef struct	s_sh
{
	unsigned long	flags;
	char			**env;
	char			*name;
	struct termios	old_terms;
	struct termios	my_terms;
	int				cursor[2];
	char			*line;
	char			*working_directory;
	char			**cmd;
	size_t			index;
	size_t			last_newline;
	size_t			size;
	char			ret[10];
	char			buffer_path[PATH_MAX + 1];
	t_blist			*history;
	t_blist			*history_ptr;
}				t_sh;

# define LINE_SIZE		2048

# define INTERNAL		"internal error"

/*
** selection colors, ls unix like (man ls)
*/

typedef struct	s_color_index
{
	int type;
	int color;
}				t_color_index;

# define SELECT_COLORS	"Gxfxcxdxbxegedabagacad"

/*
** selection structure
*/

typedef struct	s_select
{
	t_list	*selection;
	int		cursor_pos_in_line[2];
	int		original_cursor_pos[2];
	int		cursor[2];
	int		window_size[2];
	int		nb_columns;
	int		nb_lines;
	int		arg_count;
	int		arg_max_len;
	int		page;
	int		index;
}				t_select;

# define SELECT_BUFFER_SIZE	8

/*
** vertex xy position macro, usefull for cursor position
*/

# define POS(x, y)		(int[2]){(x), (y)}

/*
** shell errors
*/

enum	e_error
{
	FORK_ERROR			,
	SETATTR_ERROR		,
	FIRST_LETTER_ERROR	,
	ALNUM_ERROR			,
	NO_FILE				,
	IS_A_DIRECTORY		,
	NO_RIGHT			,
	READ_ERROR			,
	GETATTR_ERROR		,
	MALLOC_ERROR		,
	CMD_NOT_FOUND		,
	TOO_MUCH_ARG		,
};

/*
** shell flags
*/

enum	e_flags
{
	QUOTES = 0x07,
	DOUBLE_QUOTE = 0x01,
	SIMPLE_QUOTE = 0x02,
	BACKSLASH = 0x04,
	LINE_MULTIPLE = 0x08,
};

/*
** keys inputs
*/

# define KEY_ESC			(char[2]){27, 0}
# define KEY_LEFT			(char[4]){27, 91, 68, 0}
# define KEY_RIGHT			(char[4]){27, 91, 67, 0}
# define KEY_UP				(char[4]){27, 91, 65, 0}
# define KEY_DOWN			(char[4]){27, 91, 66, 0}
# define KEY_PAGE_UP		(char[5]){27, 91, 53, 126, 0}
# define KEY_PAGE_DOWN		(char[5]){27, 91, 54, 126, 0}
# define KEY_CTRL_R			(char[2]){18, 0}

/*
** e_file type use d_type from struct dirent (dirent.h)
*/

typedef struct	s_file
{
	char	*name;
	char	*path;
	int		type;
}				t_file;

/*
** prototypes
*/

void			init_shell(t_sh *sh, char **env);

void			exit_shell(t_sh *sh);

void			shell_loop(t_sh *sh);

void			get_prompt(t_sh *sh);

void			run_line_loop(t_sh *sh);

void			replace_line_buf(t_sh *sh, size_t size);

void			get_cursor_pos(int *cursor);
void			move_cursor_to(int *cursor);
void			cursor_offset(t_sh *sh, int x);

void			sh_error(int err, char *command, t_sh *sh);
void			env_error(char *key, char *command, t_sh *sh);
void			cd_error(char *arg, t_sh *sh);
void			display_sig_error(int stat, char *cmd, pid_t pid);

void			input_readable(t_sh *sh, char *buf);
void			input_non_readable(t_sh *sh, char *buf);

void			cursor_inputs(t_sh *sh, char *buf);

void			get_command_from_line(t_sh *sh, char *line);

int				parse_chars(t_sh *sh, char **line, size_t *index);

void			signal_handler(int i);

void			push_to_env(char ***env, char *key, char *value, t_sh *sh);
void			display_env(char **env);
void			new_env(char ***dst, char **src, t_sh *sh);
void			unset_env(char ***env, char *to_unset);

void			builtin_env(t_sh *sh, char **cmd);
void			builtin_setenv(t_sh *sh, char **cmd);
void			builtin_unsetenv(t_sh *sh, char **cmd);
void			builtin_echo(char **cmd);
void			builtin_cd(t_sh *sh, char **cmd);

int				is_a_builtin(t_sh *sh, char **cmd);
int				is_a_bin(t_sh *sh, char **cmd);
void			is_an_exec(t_sh *sh, char **cmd, char *path);

char			*relative_to_absolute_path(t_sh *sh, char *relative_path);

int				get_path(char **env_path, char *path);

void			execute_command(t_sh *sh, char **cmd, char *path);

void			line_push(t_sh *sh, char *buf);
void			line_delete_char(t_sh *sh);

void			autocomplete(t_sh *sh);

void			autocomplete_parse_path(t_sh *sh, t_string *path);
void			autocomplete_parse_binary(t_sh *sh, t_string *bin);
t_heuristic		autocomplete_bufcmp_in_dir(char *dir_name, t_string *str);

void			do_command(t_sh *sh, char **cmd);

void			replace_sequence(t_sh *sh, char **line, size_t len, char *by);
void			erase_spaces(char **line);

void			line_treatment(t_sh *sh, size_t index);

void			check_signal_status(int stat, char *cmd, pid_t pid);

void			get_selection_from_dir(t_select *d, char *dir, t_string *str);
void			free_selection(t_list **selection);

void			selection_display_color(t_file *file);

void			selection_move_verticaly(t_select *datas, int to);
void			selection_move_horizontaly(t_select *datas, int to);
void			selection_go_to_previous_page(t_select *datas);
void			selection_go_to_next_page(t_select *datas);

int				selection_inputs(t_select *datas, char *input);

char			*selection_loop(t_select *datas);

void			selection_display(t_select *datas);

void			move_cursor_to(int *cursor);
void			put_term_string(char *str);

char			*get_working_directory(t_sh *sh);

t_file			*new_file_from_dirent(struct dirent *dirent, char *dir_name);

void			autocomplete_best_match(t_sh *sh, char *dir, t_string *str);
int				autocomplete_selection(t_sh *sh, t_select *data, t_string *str);

#endif
