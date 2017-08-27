/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_move_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 08:11:16 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/27 05:17:42 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_index(t_select *datas, int i)
{
	return ((datas->arg_count + i) % datas->arg_count);
}

void		selection_go_to_previous_page(t_select *datas)
{
	datas->index = (datas->index
			% datas->nb_lines)
			- (datas->window_size[1] - 3);
	if (datas->index < 1)
		datas->index = 1;
}

void		selection_go_to_next_page(t_select *datas)
{
	datas->index = (datas->index
			% datas->nb_lines)
			+ datas->window_size[1] - 3;
	if (datas->index > datas->nb_lines - 2)
		datas->index = datas->nb_lines - 2;
}

void		selection_move_horizontaly(t_select *datas, int to)
{
	int			index;
	t_select	*ms;

	ms = datas;
	index = ms->index + to;
	if (index >= (int)ms->arg_count)
		index = ms->index % ms->nb_lines + 1;
	else if (index < 0)
	{
		if (ms->arg_count % ms->nb_lines
				>= ms->index % ms->nb_lines)
			index = ms->index + ms->nb_lines
				* (ms->nb_columns - 1) - 1;
		else
			index = ms->index + ms->nb_lines
				* (ms->nb_columns - 2) - 1;
	}
	ms->index = get_index(datas, index);
}

void		selection_move_verticaly(t_select *datas, int to)
{
	datas->index = get_index(datas, datas->index + to);
}
