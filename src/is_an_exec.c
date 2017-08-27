/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_an_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 06:13:13 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 06:13:32 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_an_exec(t_sh *sh, char **cmd, char *path)
{
	struct stat	infos;

	if (lstat(path, &infos) < 0)
		sh_error(NO_FILE, *cmd, sh->name);
	else if ((infos.st_mode & S_IFDIR))
		sh_error(IS_A_DIRECTORY, *cmd, sh->name);
	else if (!(infos.st_mode & S_IXUSR))
		sh_error(NO_RIGHT, *cmd, sh->name);
	else
		execute_command(sh, cmd, path);
}
