/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 10:34:00 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 04:29:26 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		display_env_error(char opt)
{
	if (opt == 'u')
		ft_putendl_fd("env: option requires an argument -- u", 2);
	else
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(opt, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putendl_fd("env [-i] [-u name] [name=value]... [utility [argument...]]"
		, 2);
	return (-1);
}

void	builtin_env_post(char **cmd, t_sh *sh)
{
	char	*tmp;

	while (*cmd && **cmd != '=' && (tmp = ft_strchr(*cmd, '=')))
	{
		*tmp = '\0';
		push_to_env(&sh->env, *cmd, tmp + 1, sh);
		cmd += 1;
	}
	if (*cmd)
		do_command(sh, cmd);
	else
		display_env(sh->env);
}

int		builtin_env_options(t_sh *sh, char **cmd, size_t *i)
{
	while (cmd[i[0]][++i[1]])
		if (cmd[i[0]][i[1]] == 'u')
		{
			if (cmd[i[0]][i[1] + 1])
			{
				unset_env(&sh->env, &cmd[i[0]][i[1] + 1]);
				return (0);
			}
			else
			{
				if (!cmd[i[0] + 1])
					return (display_env_error('u'));
				unset_env(&sh->env, cmd[(i[0] += 1)]);
				return (0);
			}
		}
		else if (cmd[i[0]][i[1]] == 'i')
			ft_free_2d(sh->env);
		else if (cmd[i[0]][i[1]] != '-')
			return (display_env_error(cmd[i[0]][i[1]]));
	return (0);
}

void	builtin_env_bis(t_sh *sh, char **cmd)
{
	int		ret;
	size_t	index[2];

	sh->name = "env";
	index[0] = 0;
	while (cmd[index[0]] && *cmd[index[0]] == '-'
			&& ft_strcmp_nocase(cmd[index[0]], "--"))
	{
		index[1] = 0;
		if ((ret = builtin_env_options(sh, cmd, index)))
			if (ret < 0)
				return ;
		index[0] += 1;
	}
	builtin_env_post(&cmd[index[0]], sh);
	exit(0);
}

void	builtin_env(t_sh *sh, char **cmd)
{
	pid_t	pid;
	int		stat;

	if (!ft_strcmp(sh->name, "env"))
		builtin_env_bis(sh, cmd + 1);
	if ((pid = fork()) < 0)
		sh_error(FORK_ERROR, *cmd, sh);
	else if (pid == 0)
		builtin_env_bis(sh, cmd + 1);
	else
	{
		waitpid(-1, &stat, 0);
		ft_utoabuf(WEXITSTATUS(stat), sh->ret);
		if (WIFSIGNALED(stat))
		{
			ft_utoabuf(_WSTATUS(stat) | 0x80, sh->ret);
			check_signal_status(stat, *cmd, pid);
		}
		if (tcsetattr(0, TCSANOW, &sh->old_terms) < 0)
			sh_error(SETATTR_ERROR, INTERNAL, sh);
	}
}
