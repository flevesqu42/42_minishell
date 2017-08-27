/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 04:34:10 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 09:07:30 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_color_foreground(int n)
{
	static char *foreground_color[127] = {
		['A']="\e[1m\e[30m",
		['B']="\e[1m\e[31m",
		['C']="\e[1m\e[32m",
		['D']="\e[1m\e[33m",
		['E']="\e[1m\e[33m",
		['F']="\e[1m\e[35m",
		['G']="\e[1m\e[36m",
		['H']="\e[1m\e[39m",
		['a']="\e[30m",
		['b']="\e[31m",
		['c']="\e[32m",
		['d']="\e[33m",
		['e']="\e[34m",
		['f']="\e[35m",
		['g']="\e[36m",
		['h']="\e[39m"
	};

	return (foreground_color[n] ? foreground_color[n] : "");
}

static char	*get_color_background(int n)
{
	static char	*background_color[127] = {
		['A']="\e[100m",
		['B']="\e[101m",
		['C']="\e[102m",
		['D']="\e[103m",
		['E']="\e[104m",
		['F']="\e[105m",
		['G']="\e[106m",
		['H']="\e[109m",
		['a']="\e[40m",
		['b']="\e[41m",
		['c']="\e[42m",
		['d']="\e[43m",
		['e']="\e[44m",
		['f']="\e[45m",
		['g']="\e[46m",
		['h']="\e[49m"
	};

	return (background_color[n] ? background_color[n] : "");
}

static int	get_color_index_by_type(int type)
{
	int							i;
	static const t_color_index	g_color[] = {
		{S_IFDIR, 0}, {S_IFLNK, 2}, {S_IFSOCK, 4}, {S_IFIFO, 6}, {S_IFBLK, 10},
		{S_IFCHR, 12}, {0, 0}};

	i = 0;
	while (g_color[i].type)
	{
		if (type == g_color[i].type)
			return (g_color[i].color);
		++i;
	}
	return (-1);
}

static int	get_color_index(int type, int st)
{
	if (type == S_IFDIR && (st & S_IWOTH))
		return ((st & S_ISVTX) ? 18 : 20);
	else if (type == S_IFDIR && st & S_IWOTH)
		return ((st & S_ISVTX) ? 18 : 20);
	else if (type == S_IFREG
			&& (st & (S_IXUSR | S_IXGRP | S_IXOTH)))
	{
		if (st & S_ISUID)
			return (14);
		else if (st & S_ISGID)
			return (16);
		return (8);
	}
	return (get_color_index_by_type(type));
}

void		selection_display_color(t_file *file)
{
	int			index;

	if ((index = get_color_index(file->type & S_IFMT, file->type)) < 0)
		return ;
	ft_putstr_fd(get_color_foreground(SELECT_COLORS[index]), 0);
	ft_putstr_fd(get_color_background(SELECT_COLORS[index + 1]), 0);
}
