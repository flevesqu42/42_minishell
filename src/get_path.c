/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 03:19:30 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/21 03:19:41 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_path(char **env_path, char *path)
{
	if (!*env_path || !**env_path)
		return (0);
	if (ft_strchr(*env_path, ':'))
	{
		ft_strncpy(path, *env_path, ft_strchr(*env_path, ':') - *env_path);
		path[ft_strchr(*env_path, ':') - *env_path] = '\0';
		*env_path += ft_strlen(path) + 1;
		return (1);
	}
	else
	{
		ft_strcpy(path, *env_path);
		*env_path += ft_strlen(path);
		return (1);
	}
}
