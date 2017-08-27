/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 03:14:12 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 10:56:29 by flevesqu         ###   ########.fr       */
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
		builtin_env(sh, cmd);
	else if (!ft_strcmp_nocase(*cmd, "setenv") && (ret = 1))
		builtin_setenv(sh, cmd);
	else if (!ft_strcmp_nocase(*cmd, "unsetenv") && (ret = 1))
		builtin_unsetenv(sh, &cmd[1]);
	else if (!ft_strcmp_nocase(*cmd, "getenv") && (ret = 1))
		ft_putendl(ft_getenv(sh->env, cmd[1]));
	else if (!ft_strcmp_nocase(*cmd, "echo") && (ret = 1))
		builtin_echo(&cmd[1]);
	else if (!ft_strcmp_nocase(*cmd, "cd") && (ret = 1))
		builtin_cd(sh, cmd + 1);
	return (ret);
}
