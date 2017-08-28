/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 04:23:02 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 08:16:46 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_element(t_list *list, size_t index)
{
	size_t	i;

	i = 0;
	while (list)
	{
		if (index == i)
			break ;
		list = list->next;
		++i;
	}
	return (((t_file*)list->data)->name);
}

static char	*select_exit(t_select *datas, char *ret)
{
	move_cursor_to(datas->original_cursor_pos);
	put_term_string("cd");
	move_cursor_to(datas->cursor_pos_in_line);
	return (ret);
}

static void	selection_set_padding(t_select *datas)
{
	int			pad;
	int			counter;

	counter = 0;
	pad = datas->nb_lines - 1;
	if (pad > datas->window_size[1] - 2)
		pad = datas->window_size[1] - 2;
	while (counter++ <= pad)
		ft_putstr_fd("\n", 0);
	get_cursor_pos(datas->cursor);
	datas->cursor[1] -= pad;
	move_cursor_to(datas->cursor);
	datas->original_cursor_pos[0] = 0;
	datas->original_cursor_pos[1] = datas->cursor[1];
	datas->cursor_pos_in_line[1] = datas->cursor[1] - 1;
	put_term_string("cd");
}

static void	get_display_info(t_select *datas)
{
	int			tmp_len;
	t_list		*current;

	current = datas->selection;
	datas->arg_max_len = 0;
	while (current)
	{
		tmp_len = ft_strlen(((t_file*)current->data)->name);
		if (tmp_len > datas->arg_max_len)
			datas->arg_max_len = tmp_len;
		current = current->next;
	}
	datas->nb_columns = datas->window_size[0] / (datas->arg_max_len + 2);
	if (!datas->nb_columns)
		datas->nb_lines = datas->window_size[1];
	else
		datas->nb_lines = (datas->arg_count / datas->nb_columns)
			+ (datas->arg_count % datas->nb_columns ? 1 : 0);
}

char		*selection_loop(t_select *s)
{
	char	input[SELECT_BUFFER_SIZE + 1];
	int		ret;

	s->window_size[0] = tgetnum("co");
	s->window_size[1] = tgetnum("li");
	s->index = 0;
	s->page = 0;
	get_cursor_pos(s->cursor_pos_in_line);
	get_display_info(s);
	selection_set_padding(s);
	while (42)
	{
		selection_display(s);
		if ((ret = read(0, input, SELECT_BUFFER_SIZE)) < 0)
			return (NULL);
		input[ret] = '\0';
		if (*input == 3 || *input == 127 || !ft_strcmp(input, KEY_ESC))
			return (select_exit(s, NULL));
		else if (*input == '\n' || *input == ' ')
			return (select_exit(s, get_element(s->selection, s->index)));
		if (selection_inputs(s, input))
			return (select_exit(s, NULL));
	}
}
