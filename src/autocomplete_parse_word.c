/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_parse_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 05:33:59 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 04:06:51 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	compare_in_dir_and_automplete(t_sh *sh, char *dir_name
	, t_string *string_to_compare)
{
	t_select	datas;

	datas.selection = NULL;
	datas.arg_count = 0;
	if (*dir_name == '~')
	{
		get_selection_from_dir(&datas, dir_name, string_to_compare);
	}
	else
		get_selection_from_dir(&datas, dir_name, string_to_compare);
	if (autocomplete_selection(sh, &datas, string_to_compare))
	{
		autocomplete_best_match(sh, dir_name, string_to_compare);
		return ;
	}
}

void		autocomplete_parse_path(t_sh *sh, t_string *path)
{
	t_string	file;

	file = ft_string_from_rchr(path, '/');
	if (*file.string != '/')
		compare_in_dir_and_automplete(sh, getcwd(sh->buffer_path, PATH_MAX)
			, &file);
	else if (file.string == path->string)
	{
		ft_string_offset(&file, +1);
		compare_in_dir_and_automplete(sh, "/", &file);
	}
	else
	{
		*file.string = '\0';
		ft_string_offset(&file, +1);
		compare_in_dir_and_automplete(sh, path->string, &file);
		file.string[-1] = '/';
	}
}

void		autocomplete_parse_binary(t_sh *sh, t_string *string_to_compare)
{
	char		*env_path;
	t_select	datas;

	if (!(env_path = ft_getenv(sh->env, "PATH")))
		return ;
	datas.selection = NULL;
	datas.arg_count = 0;
	while (get_path(&env_path, sh->buffer_path))
		get_selection_from_dir(&datas, sh->buffer_path, string_to_compare);
	if (autocomplete_selection(sh, &datas, string_to_compare))
		return ;
}
