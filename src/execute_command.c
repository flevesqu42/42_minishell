/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 06:16:08 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 10:55:06 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_sh *sh, char **cmd, char *path)
{
	pid_t	pid;
	int		stat;

	push_to_env(&sh->env, "_", path);
	if (!ft_strcmp(sh->name, "env"))
	{
		execve(path, cmd, sh->env);
		return ;
	}
	if ((pid = fork()) < 0)
		sh_error(FORK_ERROR, *cmd, sh->name);
	else if (pid == 0)
		execve(path, cmd, sh->env);
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
			sh_error(SETATTR_ERROR, INTERNAL, sh->name);
	}
}
