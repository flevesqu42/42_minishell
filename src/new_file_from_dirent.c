/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_file_from_dirent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 09:04:50 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 09:04:51 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file		*new_file_from_dirent(struct dirent *dirent, char *dir_name)
{
	t_file		*new;
	struct stat	stat;

	new = (t_file*)malloc(sizeof(t_file));
	new->path = ft_strnew(ft_strlen(dir_name) + dirent->d_namlen + 2);
	ft_strcat(new->path, dir_name);
	ft_strcat(new->path, "/");
	ft_strcat(new->path, dirent->d_name);
	lstat(new->path, &stat);
	new->type = stat.st_mode;
	if ((new->type & S_IFMT) == S_IFDIR)
		new->name = ft_strjoin(dirent->d_name, "/");
	else
		new->name = ft_strdup(dirent->d_name);
	return (new);
}
