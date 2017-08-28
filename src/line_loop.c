/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 04:26:01 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 04:26:07 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_loop(t_sh *sh)
{
	char			buf[9];
	int				ret;

	*buf = '\0';
	get_cursor_pos(sh->cursor);
	while (*buf != 3 && *buf != '\n')
	{
		if ((ret = read(0, buf, 1)) < 0)
			sh_error(READ_ERROR, INTERNAL, sh);
		buf[ret] = '\0';
		if (ft_isprint(*buf) || *buf == '\n')
			input_readable(sh, buf);
		else
			input_non_readable(sh, buf);
	}
	ft_putchar_fd('\n', 0);
}

void		run_line_loop(t_sh *sh)
{
	sh->last_newline = sh->index;
	if (tcsetattr(0, TCSANOW, &sh->my_terms) < 0)
		sh_error(SETATTR_ERROR, INTERNAL, sh);
	put_term_string("cd");
	edit_loop(sh);
	if (tcsetattr(0, TCSANOW, &sh->old_terms) < 0)
		sh_error(SETATTR_ERROR, INTERNAL, sh);
}
