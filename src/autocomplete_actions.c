/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 03:59:39 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 08:26:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_autocomplete(t_sh *sh, t_string *word, char *name)
{
	if (!name)
		return ;
	ft_memmove(word->string, word->string + word->len
			, ft_strlen(word->string + word->len) + 1);
	sh->index -= word->len;
	cursor_offset(sh, -word->len);
	line_push(sh, name);
}

void		autocomplete_best_match(t_sh *sh, char *dir_name
		, t_string *string_to_compare)
{
	t_heuristic	matched_name;

	matched_name = autocomplete_bufcmp_in_dir(dir_name, string_to_compare);
	if (matched_name.heuristic > 0)
		set_autocomplete(sh, string_to_compare, matched_name.data);
	if (matched_name.data)
		free(matched_name.data);
}

int			autocomplete_selection(t_sh *sh, t_select *datas
	, t_string *string_to_compare)
{
	char		*selected_name;

	if (!datas->selection)
		return (1);
	if (!datas->selection->next)
		set_autocomplete(sh, string_to_compare
				, ((t_file*)datas->selection->data)->name);
	else
	{
		selected_name = selection_loop(datas);
		sh->cursor[0] = datas->cursor_pos_in_line[0];
		sh->cursor[1] = datas->cursor_pos_in_line[1];
		set_autocomplete(sh, string_to_compare, selected_name);
	}
	free_selection(&datas->selection);
	return (0);
}
