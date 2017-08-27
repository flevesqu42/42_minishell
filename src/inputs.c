/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 03:59:12 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 04:11:27 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_readable(t_sh *sh, char *buf)
{
	if (*buf == '\n')
		sh->index = ft_strlen(sh->line);
	line_push(sh, buf);
}

void	input_non_readable(t_sh *sh, char *buf)
{
	if (*buf == 4)
		sh->line[0] ? ft_putchar_fd(7, 0) : exit_shell(sh);
	else if (*buf == '\t')
		autocomplete(sh);
	else if (*buf == 12)
	{
		ft_putchar_fd('\n', 0);
		put_term_string("cl");
		get_prompt(sh);
		ft_putstr_fd(sh->line, 0);
		get_cursor_pos(sh->cursor);
		sh->index = ft_strlen(sh->line);
	}
	else if (*buf == 3)
		*sh->line = '\0';
	else if (*buf == 127 && sh->index && sh->index > sh->last_newline)
		line_delete_char(sh);
	else if (*buf == 27)
		cursor_inputs(sh, buf);
}
