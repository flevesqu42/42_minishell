/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_bufcmp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 07:12:57 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 03:56:15 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_match_heuristic(t_string *str, char *dir)
{
	int		match_heuristic;
	char	*match;
	char	tmp;

	match_heuristic = -999;
	tmp = str->string[str->len];
	str->string[str->len] = '\0';
	if ((match = ft_strstr(dir, str->string)))
		match_heuristic = (str->len * 4) - (match - dir);
	str->string[str->len] = tmp;
	return (match_heuristic);
}

static int	get_heuristic(t_string *str, char *dir)
{
	size_t	index;
	int		heuristic;
	int		match_heuristic;

	index = 0;
	heuristic = 0;
	if (!ft_strcmp(".", dir) || !ft_strcmp("..", dir))
		return (-666);
	while (index < str->len)
	{
		if (dir[index] == str->string[index])
			heuristic += 2;
		else if (ft_toupper(dir[index]) == ft_toupper(str->string[index]))
			heuristic += 1;
		else
			heuristic -= 1;
		if (!dir[index])
			break ;
		++index;
	}
	match_heuristic = get_match_heuristic(str, dir);
	return (heuristic > match_heuristic ? heuristic : match_heuristic);
}

t_heuristic	autocomplete_bufcmp_in_dir(char *dir_name, t_string *str)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				tmp_heuristic;
	t_heuristic		best_name;

	best_name = ft_new_heuristic(NULL, -666);
	if (!(dir = opendir(dir_name)))
		return (best_name);
	while ((dirent = readdir(dir)))
	{
		if ((tmp_heuristic = get_heuristic(str
				, dirent->d_name)) > best_name.heuristic)
		{
			if (best_name.data)
				free(best_name.data);
			if (dirent->d_type == DT_DIR)
				best_name.data = ft_strjoin(dirent->d_name, "/");
			else
				best_name.data = ft_strdup(dirent->d_name);
			best_name.heuristic = tmp_heuristic;
		}
	}
	closedir(dir);
	return (best_name);
}
