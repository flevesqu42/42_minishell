/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 04:20:28 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 06:50:52 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_directory_to(t_sh *sh, char *path, int flag
	, char *original_path)
{
	char	*pwd;

	path = ft_strdup(path);
	if (chdir(path) < 0)
		cd_error(original_path);
	else
	{
		if ((pwd = ft_getenv(sh->env, "PWD")))
			push_to_env(&sh->env, "OLDPWD", pwd);
		if (flag)
			push_to_env(&sh->env, "PWD", getcwd(sh->buffer_path, PATH_MAX));
		else
			push_to_env(&sh->env, "PWD", path);
	}
	free(path);
}

static void	cd_to_envpath(t_sh *sh, char *key, int flag, char *original_path)
{
	char	*path;

	if (!(path = ft_getenv(sh->env, key)))
		env_error(key, "cd", sh->name);
	else
		change_directory_to(sh, path, flag, original_path);
}

static int	parse_flags(char *word)
{
	int	flag;

	flag = 0;
	while (*(++word))
		if (*word == 'P')
			flag |= 1;
		else if (*word != 'L')
		{
			ft_putstr_fd("cd: -", 2);
			ft_putchar_fd(*word, 2);
			ft_putstr_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]\n", 2);
			return (-1);
		}
	return (flag);
}

void		builtin_cd(t_sh *sh, char **arg)
{
	int			flag;

	flag = 0;
	while (*arg && **arg == '-' && (*arg)[1])
	{
		if (!ft_strcmp("--", *arg))
			break ;
		if ((flag |= parse_flags(*arg)) < 0)
			return ;
		++arg;
	}
	if (!*arg)
		cd_to_envpath(sh, "HOME", flag, *arg);
	else if (!ft_strcmp(*arg, "-"))
		cd_to_envpath(sh, "OLDPWD", flag, *arg);
	else
		change_directory_to(sh, relative_to_absolute_path(sh, *arg), flag
			, *arg);
}
