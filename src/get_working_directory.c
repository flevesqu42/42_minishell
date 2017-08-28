/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_working_directory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 08:42:52 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/26 06:51:22 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_working_directory(t_sh *sh)
{
	char	*wd;

	if (!(wd = ft_getenv(sh->env, "PWD")))
	{
		getcwd(sh->buffer_path, PATH_MAX);
		wd = sh->buffer_path;
		push_to_env(&sh->env, "PWD", wd, sh);
	}
	else
		wd = ft_strcpy(sh->buffer_path, wd);
	return (wd);
}
