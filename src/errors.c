/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 05:34:51 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 08:35:12 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_error(int err, char *command, t_sh *sh)
{
	static char	*str[] = {
		": cannot create new process\n",
		": cannot set termcaps attributes\n",
		": Variable name must begin with a letter.\n",
		": Variable name must contain alphanumeric characters.\n",
		": No such file or directory\n",
		": is a directory\n",
		": permission denied\n",
		": can't read standard input\n",
		": cannot get termcaps attributes\n",
		": memory allocation failed\n",
		": command not found\n",
		": too much arguments\n",
	};

	ft_putstr_fd(sh->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(str[err], 2);
	if (err == READ_ERROR || err == MALLOC_ERROR || err == GETATTR_ERROR
			|| err == SETATTR_ERROR)
		exit(1);
	ft_utoabuf(1, sh->ret);
}

void	env_error(char *key, char *command, t_sh *sh)
{
	ft_putstr_fd(sh->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not set\n", 2);
	ft_utoabuf(1, sh->ret);
}

void	cd_error(char *arg, t_sh *sh)
{
	struct stat	infos;

	ft_putstr_fd(sh->name, 2);
	ft_putstr_fd(": cd: ", 2);
	ft_putstr_fd(arg, 2);
	if (lstat(arg, &infos) < 0)
		ft_putstr_fd(": no such file or directory\n", 2);
	else if (!(infos.st_mode & S_IFDIR))
		ft_putstr_fd(": not a directory\n", 2);
	else if (!(infos.st_mode & S_IXUSR))
		ft_putstr_fd(": permission denied\n", 2);
	else
		ft_putstr_fd(": can't proceed to change directory here.\n", 2);
	ft_utoabuf(1, sh->ret);
}

void	display_sig_error(int stat, char *cmd, pid_t pid)
{
	ft_putstr_fd("[1]    ", 2);
	ft_putnbr_fd(pid, 2);
	if (stat == SIGSEGV)
		ft_putstr_fd(" segmentation fault  ", 2);
	else if (stat == SIGBUS)
		ft_putstr_fd(" bus error  ", 2);
	else if (stat == SIGQUIT)
		ft_putstr_fd(" quit  ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}
