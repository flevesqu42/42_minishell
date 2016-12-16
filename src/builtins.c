/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:52:26 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/16 07:10:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_a_builtin(t_sh *sh, char **cmd)
{
	int		ret;

	ret = 0;
	if (!ft_strcmp_nocase(*cmd, "exit") && (ret = 1))
		exit_shell(sh);
	else if (!ft_strcmp_nocase(*cmd, "env") && (ret = 1))
		env_built(sh, cmd);
	else if (!ft_strcmp_nocase(*cmd, "setenv") && (ret = 1))
		set_env_built(sh, cmd);
	else if (!ft_strcmp_nocase(*cmd, "unsetenv") && (ret = 1))
		unset_env_built(sh, &cmd[1]);
	else if (!ft_strcmp_nocase(*cmd, "getenv") && (ret = 1))
		ft_putendl(ft_getenv(sh->env, cmd[1]));
	else if (!ft_strcmp_nocase(*cmd, "echo") && (ret = 1))
		echo_built(&cmd[1]);
	else if (!ft_strcmp_nocase(*cmd, "cd") && (ret = 1))
		change_directory(sh, cmd[1]);
	return (ret);
}

void	exit_shell(t_sh *sh)
{
	if (tcsetattr(0, TCSANOW, &sh->old_terms) < 0)
		sh_error(SETATTR_ERROR, "internal", "minishell");
	ft_putstr_fd("exit\n", 0);
	exit(0);
}

void	set_env_built(t_sh *sh, char **cmd)
{
	size_t index;

	index = 0;
	if (!cmd[1])
		display_env(sh->env);
	else if (cmd[1] && cmd[2] && cmd[3])
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else if (!ft_isalpha(*cmd[1]) && *cmd[1] != '_')
		sh_error(FIRST_LETTER_ERROR, "setenv", sh->name);
	else
	{
		while (ft_isalnum(cmd[1][index]) || cmd[1][index] == '_')
			++index;
		if (cmd[1][index])
			sh_error(ALNUM_ERROR, "setenv", sh->name);
		else
			push_to_env(&sh->env, cmd[1], cmd[2]);
	}
}

void	echo_char_sequence(char *str, int *flag)
{
	if (str[1] == 'a' || str[1] == 'b' || str[1] == 'f' || str[1] == 'n'
			|| str[1] == 'r' || str[1] == 't' || str[1] == 'v')
	{
		if (str[1] == 'a')
			str[0] = '\a';
		if (str[1] == 'b')
			str[0] = '\b';
		if (str[1] == 'f')
			str[0] = '\f';
		if (str[1] == 'n')
			str[0] = '\n';
		if (str[1] == 'r')
			str[0] = '\r';
		if (str[1] == 't')
			str[0] = '\t';
		if (str[1] == 'v')
			str[0] = '\v';
		ft_memmove(&str[1], &str[2], ft_strlen(&str[2]) + 1);
	}
	else if (str[1] == 'c')
	{
		*flag |= 0x1;
		str[0] = '\0';
		str[1] = '\0';
	}
	else if (str[1] == '\\')
		ft_memmove(&str[0], &str[1], ft_strlen(&str[1]) + 1);
}

void	echo_built(char **cmd)
{
	size_t	index[2];
	int		flags;

	index[0] = 0;
	while (cmd[index[0]])
	{
		index[1] = 0;
		while (cmd[index[0]][index[1]])
		{
			if (cmd[index[0]][index[1]] == '\\' && cmd[index[0]][index[1] + 1])
				echo_char_sequence(&cmd[index[0]][index[1]], &flags);
			++index[1];
		}
		if (index[0])
			ft_putchar(' ');
		ft_putstr(cmd[index[0]]);
		++index[0];
	}
	if (!flags)
		ft_putchar('\n');
}

void	unset_env_built(t_sh *sh, char **cmd)
{
	size_t	index;

	index = 0;
	if (!*cmd)
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
	while (cmd[index])
	{
		unset_env(&sh->env, cmd[index]);
		++index;
	}
}

void	change_directory(t_sh *sh, char *arg)
{
	struct stat infos;

	if ((!arg || !ft_strcmp_nocase(arg, "--")) && !(arg = ft_getenv(sh->env, "HOME")))
		sh_error(HOME_NOT_SET, "cd", sh->name);
	else if (!ft_strcmp_nocase(arg, "-") && !(arg = ft_getenv(sh->env, "OLDPWD")))
		ft_putendl_fd("cd: OLDPWD not set", 2);
	else if (chdir(arg) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		if (lstat(arg, &infos) < 0)
			ft_putstr_fd(": no such file or directory\n", 2);
		else if (!(infos.st_mode & S_IFDIR))
			ft_putstr_fd(": not a directory\n", 2);
		else if (!(infos.st_mode & S_IXUSR))
			ft_putstr_fd(": permission denied\n", 2);
		else
			ft_putstr_fd(": can't proceed to change directory here.\n", 2);
	}
	else
		push_to_env(&sh->env, "OLDPWD", ft_getenv(sh->env, "PWD"));
}
