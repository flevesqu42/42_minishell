/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 05:51:35 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 08:56:59 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_in_directory(t_sh *sh, char **cmd	, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;

	ft_strcat(path, "/");
	if (!(dir = opendir(path)))
		return (0);
	while ((dirent = readdir(dir)))
	{
		if (!ft_strcmp_nocase(*cmd, dirent->d_name))
		{
			ft_strcat(path, dirent->d_name);
			is_an_exec(sh, cmd, path);
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int			is_a_bin(t_sh *sh, char **cmd)
{
	char	*env_path;

	if (!(env_path = ft_getenv(sh->env, "PATH")))
		return (0);
	while (get_path(&env_path, sh->buffer_path))
		if (check_in_directory(sh, cmd, sh->buffer_path))
			return (1);
	return (0);
}
