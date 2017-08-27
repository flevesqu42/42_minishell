/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 04:08:52 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 11:20:54 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cursor_move_index(t_sh *sh, int to)
{
	cursor_offset(sh, to);
	sh->index += to;
}

static void	replace_line(t_sh *sh, char *by)
{
	cursor_move_index(sh, -sh->index);
	*sh->line = '\0';
	line_push(sh, by);
}

static void	set_previous_history_line(t_sh *sh)
{
	replace_line(sh, sh->history_ptr->data);
	if (sh->history_ptr->next)
		sh->history_ptr = sh->history_ptr->next;
}

static void	set_next_history_line(t_sh *sh)
{
	if (sh->history_ptr->prev)
	{
		replace_line(sh, sh->history_ptr->prev->data);
		sh->history_ptr = sh->history_ptr->prev;
	}
	else
	{
		cursor_move_index(sh, -sh->index);
		*sh->line = '\0';
		put_term_string("cd");
	}
}

void		cursor_inputs(t_sh *sh, char *buf)
{
	int	ret;

	if ((ret = read(0, buf + 1, 7)) < 0)
		sh_error(READ_ERROR, INTERNAL, sh->name);
	buf[ret + 1] = '\0';
	if (!ft_strcmp(buf, KEY_LEFT) && sh->index && sh->index > sh->last_newline)
		cursor_move_index(sh, -1);
	else if (!ft_strcmp(buf, KEY_RIGHT) && sh->line[sh->index])
		cursor_move_index(sh, +1);
	else if (!ft_strcmp(buf, KEY_UP) && sh->history_ptr)
		set_previous_history_line(sh);
	else if (!ft_strcmp(buf, KEY_DOWN) && sh->history_ptr)
		set_next_history_line(sh);
}
