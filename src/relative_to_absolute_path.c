/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_to_absolute_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 06:35:32 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 06:39:58 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_updir(char *curpath, char *from)
{
	if (curpath == from--)
		return (curpath + 1);
	while (*from == '/')
		if (curpath == from--)
			return (curpath + 1);
	from[1] = '\0';
	while (*from != '/')
		if (curpath == from--)
			return (curpath + 1);
	return (from + 1);
}

static char	*go_updir(char *curpath, char *from)
{
	char		*updir;

	updir = get_updir(curpath, from);
	ft_memmove(updir, from + 2, ft_strlen(from + 2) + 1);
	return (updir);
}

static void	clear_slashs(char *curpath)
{
	char	*slash;
	char	*ptr;

	ptr = curpath;
	while (*ptr && ptr[1])
	{
		if (ptr[0] == '/' && ptr[1] == '/')
		{
			slash = ptr + 1;
			while (*slash == '/')
				++slash;
			ft_memmove(ptr + 1, slash, ft_strlen(slash) + 1);
		}
		else
			++ptr;
	}
	if (*ptr == '/' && ptr != curpath)
		*ptr = '\0';
}

static void	parse_curpath(char *curpath)
{
	char	*ptr;

	ptr = curpath;
	while (*ptr)
	{
		if (*ptr == '/')
		{
			++ptr;
			if (*ptr == '.' && !ptr[1])
				*ptr = '\0';
			else if (*ptr == '.' && ptr[1] == '/')
				ft_memmove(ptr, ptr + 2, ft_strlen(ptr + 2) + 1);
			else if (*ptr == '.' && ptr[1] == '.' && (ptr[2] == '/' || !ptr[2]))
				ptr = go_updir(curpath, ptr);
		}
		else
			++ptr;
	}
	clear_slashs(curpath);
}

char		*relative_to_absolute_path(t_sh *sh, char *relative_path)
{
	char	*curpath;
	int		len;

	if (*relative_path == '/')
		curpath = ft_strcpy(sh->buffer_path, relative_path);
	else
	{
		curpath = get_working_directory(sh);
		len = ft_strlen(curpath);
		if (curpath[len - 1] != '/')
		{
			curpath[len] = '/';
			curpath[len + 1] = '\0';
		}
		ft_strcat(curpath + len, relative_path);
	}
	parse_curpath(curpath);
	return (curpath);
}
