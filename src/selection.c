/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 04:29:13 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 09:09:46 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_selection(t_list **selection)
{
	if (!*selection)
		return ;
	free_selection(&(*selection)->next);
	free(((t_file*)(*selection)->data)->path);
	((t_file*)(*selection)->data)->path = NULL;
	free(((t_file*)(*selection)->data)->name);
	((t_file*)(*selection)->data)->name = NULL;
	free((*selection)->data);
	(*selection)->data = NULL;
	free(*selection);
	*selection = NULL;
}

void	get_selection_from_dir(t_select *datas, char *dir_name
						, t_string *string_to_compare)
{
	struct dirent	*dirent;
	DIR				*dir;

	if (!(dir = opendir(dir_name)))
		return ;
	while ((dirent = readdir(dir)))
		if (ft_strcmp(dirent->d_name, ".") && ft_strcmp(dirent->d_name, "..")
				&& !ft_strncmp_nocase(string_to_compare->string, dirent->d_name
				, string_to_compare->len))
		{
			ft_lstpushnew(&datas->selection, new_file_from_dirent(dirent
				, dir_name));
			datas->arg_count += 1;
		}
	closedir(dir);
}
