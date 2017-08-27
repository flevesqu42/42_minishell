/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 05:34:51 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 01:47:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	critical_error(int err)
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

void		sh_error(int err, char *command, char *sh)
{
	if (err == READ_ERROR || err == MALLOC_ERROR || err == GETATTR_ERROR
			|| err == SETATTR_ERROR)
		critical_error(err);
	ft_putstr_fd(sh, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	if (err == CMD_NOT_FOUND)
		ft_putstr_fd(": command not found\n", 2);
	else if (err == TOO_MUCH_ARG)
		ft_putstr_fd(": too much arguments\n", 2);
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
}

void		env_error(char *key, char *command, char *sh)
{
	ft_putstr_fd(sh, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not set\n", 2);
}

void		cd_error(char *arg)
{
	struct stat	infos;

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

void		display_sig_error(int stat, char *cmd, pid_t pid)
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
