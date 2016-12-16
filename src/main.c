/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:58:57 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/16 10:45:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_prompt(t_sh *sh)
{
    char	wd[PATH_MAX + 1];
	char	*home;

	ft_strcpy(sh->prompt, "\e[38;5;208mᐂ\e[90m [");
	getcwd(wd, PATH_MAX);
	push_to_env(&sh->env, "PWD", wd);
	if ((home = ft_getenv(sh->env, "HOME")) && *home
		&& !ft_strncmp(wd, home, ft_strlen(home)))
	{
		*wd = '~';
		ft_strcpy(&wd[1], &wd[ft_strlen(home)]);
	}
	ft_strcat(sh->prompt, wd);
	ft_strcat(sh->prompt, "]\e[0m >_ ");
	ft_putstr_fd(sh->prompt, 2);
}

void	signal_handler(int i)
{
	if (i == 2)
		ft_putchar_fd('\n', 0);
}

void	init_shell(t_sh *sh, char **env)
{
	char			*shlvl;
	char			buf[11];

	sh->flags = 0;
	sh->env = NULL;
	sh->name = "minishell";
	new_env(&sh->env, env);
	if ((shlvl = ft_getenv(sh->env, "SHLVL")))
		push_to_env(&sh->env, "SHLVL", ft_utoasub(ft_atoi(shlvl) < 0 ? 0
			: ft_atoi(shlvl) + 1, buf));
	else
		push_to_env(&sh->env, "SHLVL", "1");
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	if (tgetent(NULL, ft_getenv(sh->env, "TERM")) <= 0)
		if (tgetent(NULL, "xterm-256color") <= 0)
			sh_error(GETATTR_ERROR, "internal", sh->name);
	if (tcgetattr(0, &sh->old_terms) < 0)
		sh_error(GETATTR_ERROR, "internal", sh->name);
	sh->my_terms = sh->old_terms;
	sh->my_terms.c_lflag &= ~(ICANON | ECHO);
	sh->my_terms.c_cc[VMIN] = 1;
	sh->my_terms.c_cc[VTIME] = 0;
	sh->my_terms.c_cc[VINTR] = 0;
}

void	sh_error(int err, char *command, char *sh)
{
	if (err == READ_ERROR || err == MALLOC_ERROR || err == GETATTR_ERROR
			|| err == SETATTR_ERROR)
	{
		if (err == READ_ERROR)
			ft_putstr_fd("minishell: can't read standard input\n", 2);
		else if (err == MALLOC_ERROR)
			ft_putstr_fd("minishell: memory allocation failed\n", 2);
		else if (err == GETATTR_ERROR)
			ft_putstr_fd("minishell: cannot get termcaps attributes\n", 2);
		else if (err == SETATTR_ERROR)
			ft_putstr_fd("minishell: cannot set termcaps attributes\n", 2);
		exit(1);
	}
	else
	{
		ft_putstr_fd(sh, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(command, 2);
		if (err == CMD_NOT_FOUND)
			ft_putstr_fd(": command not found\n", 2);
		else if (err == CMD_TOO_LONG)
			ft_putstr_fd(": command too long\n", 2);
		else if (err == FORK_ERROR)
			ft_putstr_fd(": cannot create new process\n", 2);
		else if (err == NO_FILE)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (err == NO_RIGHT)
			ft_putstr_fd(": permission denied\n", 2);
		else if (err == FIRST_LETTER_ERROR)
			ft_putstr_fd(": Variable name must begin with a letter.\n", 2);
		else if (err == IS_A_DIRECTORY)
			ft_putstr_fd(": is a directory\n", 2);
		else if (err == ALNUM_ERROR)
			ft_putstr_fd(": Variable name must contain alphanumeric"
				" characters.\n", 2);
		else if (err == HOME_NOT_SET)
			ft_putendl_fd(": HOME not set", 2);
	}
}

int		check_termcaps(t_sh *sh, char *buf, char *cmd, size_t *index)
{
	int		ret;

	ret = 0;
	if (*buf == 4 && (ret = 1))
		*cmd ? ft_putchar_fd(7, 0) : exit_shell(sh);
	else if (*buf == 12 && (ret = 1))
	{
		ft_putchar_fd('\n', 0);
		tputs(tgetstr("cl", NULL), 0, ft_putchar);
		get_prompt(sh);
		ft_putstr_fd(cmd, 0);
	}
	else if (*buf == 3 && (ret = 1))
	{
		ft_putchar_fd('\n', 0);
		*cmd = '\0';
	}
	else if (*buf == 127 && (ret = 1) && *cmd)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		ft_putstr_fd(tgetstr("dc", NULL), 0);
		cmd[*index - 1] = '\0';
		*index -= 1;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && !buf[3]
			&& (ret = 1) && *index)
	{
		ft_putstr_fd(tgetstr("le", NULL), 0);
		*index -= 1;
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && !buf[3]
			&& (ret = 1) && buf[*index])
	{
		ft_putstr_fd(tgetstr("nd", NULL), 0);
		*index += 1;
	}
	return (ret);
}

void	push_str(char *dst, char *src, size_t *index)
{
	ft_memmove(dst + *index + ft_strlen(src), dst + *index
		, ft_strlen(dst + *index) + 1);
	ft_memmove(dst + *index, src, ft_strlen(src));
	*index += ft_strlen(src);
}

void	line_edit(t_sh *sh, char *cmd)
{
	char			buf[8];
	int				ret;
	size_t			index;

	*buf = '\0';
	*cmd = '\0';
	index = 0;
	while (*buf != 3 && (*buf != '\n' || (sh->flags & QUOTES)))
	{
		*buf == '\\' ? (sh->flags ^= BACKSLASH) : (sh->flags &= ~(BACKSLASH));
		if ((ret = read(0, buf, 8)) < 0)
			sh_error(READ_ERROR, "internal", sh->name);
		buf[ret] = '\0';
		if (*buf == '\'' && !(sh->flags & (DOUBLE_QUOTE)))
			sh->flags ^= SIMPLE_QUOTE;
		else if (*buf == '\"' && !(sh->flags & (SIMPLE_QUOTE | BACKSLASH)))
			sh->flags ^= DOUBLE_QUOTE;
		if (!check_termcaps(sh, buf, cmd, &index))
		{
			push_str(cmd, buf, &index);
			ft_putstr(buf);
			if (*buf == '\n' && (sh->flags & QUOTES))
				ft_putstr_fd("\e[31m/ \e[0m", 0);
		}
	}
}

void	shell_loop(t_sh *sh)
{
	char			cmd[2048];

	while (42)
	{
		get_prompt(sh);
		if (tcsetattr(0, TCSANOW, &sh->my_terms) < 0)
			sh_error(SETATTR_ERROR, "internal", sh->name);
		line_edit(sh, cmd);
		if (tcsetattr(0, TCSANOW, &sh->old_terms) < 0)
			sh_error(SETATTR_ERROR, "internal", sh->name);
		treat_line(sh, cmd);
	}
}

int		main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void)ac;
	(void)av;
	init_shell(&sh, env);
	shell_loop(&sh);
	return (0);
}
