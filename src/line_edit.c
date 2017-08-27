/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:51:29 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 07:29:06 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_sequence(t_sh *sh, char **line, size_t len, char *by)
{
	size_t	diff;

	diff = *line - sh->line;
	replace_line_buf(sh, diff + ft_strlen(*line + len)
		+ ft_strlen(by) + 1);
	*line = sh->line + diff;
	ft_memmove(*line + len + ft_strlen(by), *line + len
		, ft_strlen(*line + len) + 1);
	ft_memmove(*line + len, by, ft_strlen(by));
	ft_memmove(*line, *line + len, ft_strlen(*line + len) + 1);
	*line += ft_strlen(by) - 1;
}

void		erase_spaces(char **line)
{
	while (ft_isspace(**line))
	{
		**line = 1;
		*line += 1;
	}
}

void		line_push(t_sh *sh, char *buf)
{
	int len;

	len = ft_strlen(buf);
	replace_line_buf(sh, ft_strlen(sh->line) + len + 1);
	ft_memmove(sh->line + sh->index + len, sh->line + sh->index
		, ft_strlen(sh->line + sh->index) + 1);
	ft_memmove(sh->line + sh->index, buf, len);
	if (sh->cursor[1] + ((ft_strlen(&sh->line[sh->index]) + sh->cursor[0])
			/ tgetnum("co")) >= (unsigned int)tgetnum("li"))
		sh->cursor[1] -= 1;
	if (*buf != '\n')
	{
		put_term_string("cd");
		ft_putstr_fd(&sh->line[sh->index], 0);
		sh->index += len;
		ft_putchar_fd(' ', 0);
	}
	else
		sh->index += len;
	cursor_offset(sh, +len);
}

void		line_delete_char(t_sh *sh)
{
	ft_memmove(sh->line + sh->index - 1, sh->line + sh->index
		, ft_strlen(sh->line + sh->index) + 1);
	cursor_offset(sh, -1);
	put_term_string("cd");
	ft_putstr_fd(&sh->line[sh->index - 1], 0);
	move_cursor_to(POS(sh->cursor[0], sh->cursor[1]));
	sh->index -= 1;
}
