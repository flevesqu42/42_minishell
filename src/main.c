/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:58:57 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/12 04:39:19 by flevesqu         ###   ########.fr       */
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

void	init_shell(t_sh *sh, char **env)
{
	char	*shlvl;
	char	buf[11];

	sh->flags = 0;
	sh->env = NULL;
	sh->name = "minishell";
	new_env(&sh->env, env);
	if ((shlvl = ft_getenv(sh->env, "SHLVL")))
		push_to_env(&sh->env, "SHLVL", ft_utoasub(ft_atoi(shlvl) < 0 ? 0
			: ft_atoi(shlvl) + 1, buf));
	else
		push_to_env(&sh->env, "SHLVL", "1");
}

void	sh_error(int err, char *command, char *sh)
{
	if (err == READ_ERROR || err == MALLOC_ERROR)
	{
		if (err == READ_ERROR)
			ft_putstr_fd("minishell: can't read standard input\n", 2);
		else if (err == MALLOC_ERROR)
			ft_putstr_fd("minishell: memory allocation failed\n", 2);
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

void	do_nothing(int i)
{
	ft_putchar_fd('\n', 2);
	(void)i;
}

void	shell_loop(t_sh *sh)
{
	char	cmd[2049];
	int		ret;

	signal(SIGINT, do_nothing);
	while (42)
	{
		ret = 0;
		get_prompt(sh);
		if ((ret = read(0, cmd, 1024)) < 0)
			continue ;
		else if (!ret)
			exit_shell();
		else if (ret == 1)
			continue ;
		cmd[ret - 1] = '\0';
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
