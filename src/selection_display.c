/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:44:31 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 06:15:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_name(t_select *datas, int pos[2], t_file *argument
		, int index)
{
	char	buffer[datas->arg_max_len + 1];
	int		len;

	selection_display_color(argument);
	buffer[datas->arg_max_len] = '\0';
	ft_memset(buffer, ' ', datas->arg_max_len);
	len = ft_strlen(argument->name);
	move_cursor_to(pos);
	if (index == datas->index)
		ft_putstr_fd("\e[0m\e[38;5;0m\e[48;5;7m", 0);
	ft_memcpy(buffer, argument->name, len);
	write(0, buffer, datas->arg_max_len);
	put_term_string("me");
}

static void	print_argument(t_select *datas, t_file *argument, int index)
{
	static int	pos[2];

	pos[0] = datas->cursor[0] + ((datas->arg_max_len + 2)
		* (index / datas->nb_lines));
	pos[1] = datas->cursor[1] + (index % (datas->nb_lines))
			- datas->page;
	if (pos[0] >= 0 && pos[0] + datas->arg_max_len
			< datas->window_size[0] && pos[1] >= 1
			&& pos[1] < datas->window_size[1])
		print_name(datas, pos, argument, index);
}

static void	selection_set_page(t_select *datas)
{
	int relative_index_pos;
	int absolute_index_pos;

	relative_index_pos = datas->cursor[1] + (datas->index
		% datas->nb_lines) - datas->page;
	absolute_index_pos = datas->cursor[1]
		+ (datas->index % datas->nb_lines);
	if (relative_index_pos < 1)
		datas->page = absolute_index_pos - 1;
	else if (relative_index_pos > (datas->window_size[1] - 2))
	{
		if (absolute_index_pos < datas->nb_lines - 1)
			datas->page = absolute_index_pos
				- (datas->window_size[1] - 2);
		else
			datas->page = absolute_index_pos
				- (datas->window_size[1] - 1);
	}
}

void		selection_display(t_select *datas)
{
	int			index;
	t_list		*current;

	put_term_string("cd");
	selection_set_page(datas);
	current = datas->selection;
	index = 0;
	while (current)
	{
		print_argument(datas, current->data, index);
		current = current->next;
		++index;
	}
	move_cursor_to(datas->cursor_pos_in_line);
}
