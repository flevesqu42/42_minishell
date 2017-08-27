/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_inputs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:43:21 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 09:25:53 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		selection_inputs(t_select *datas, char *input)
{
	if (*input == '\t')
		selection_move_verticaly(datas, +1);
	else if (!ft_strcmp(input, KEY_PAGE_UP))
		selection_go_to_previous_page(datas);
	else if (!ft_strcmp(input, KEY_PAGE_DOWN))
		selection_go_to_next_page(datas);
	else if (!ft_strcmp(input, KEY_LEFT))
		selection_move_horizontaly(datas, -datas->nb_lines);
	else if (!ft_strcmp(input, KEY_RIGHT))
		selection_move_horizontaly(datas, +datas->nb_lines);
	else if (!ft_strcmp(input, KEY_UP))
		selection_move_verticaly(datas, -1);
	else if (!ft_strcmp(input, KEY_DOWN))
		selection_move_verticaly(datas, +1);
	else
		return (1);
	return (0);
}
