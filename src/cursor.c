/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 00:51:21 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 04:08:58 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cursor_offset(t_sh *sh, int x)
{
	int	len;

	len = x < 0 ? -x : x;
	x = x < 0 ? -1 : 1;
	while (len--)
		if (x > 0 && sh->cursor[0] >= tgetnum("co") - 1)
			if (sh->cursor[1] >= tgetnum("li") - 1)
				move_cursor_to(POS((sh->cursor[0] = 0)
					, (sh->cursor[1] = tgetnum("co") - 1)));
			else
				move_cursor_to(POS((sh->cursor[0] = 0)
					, (sh->cursor[1] = sh->cursor[1] + 1)));
		else if (x < 0 && sh->cursor[0] - 1 < 0)
			move_cursor_to(POS((sh->cursor[0] = tgetnum("co") - 1)
				, (sh->cursor[1] = sh->cursor[1] - 1)));
		else
			move_cursor_to(POS((sh->cursor[0] = sh->cursor[0] + x)
				, (sh->cursor[1] = sh->cursor[1])));
}

void	get_cursor_pos(int *cursor)
{
	char			buf[65];
	int				ret;
	int				index;

	ft_putstr_fd("\e[6n", 0);
	while ((ret = read(0, buf, 64)) < 6)
		continue ;
	buf[ret] = '\0';
	cursor[1] = ft_atoi(&buf[2]) - 1;
	index = 2;
	while (ft_isdigit(buf[index]))
		++index;
	cursor[0] = ft_atoi(&buf[index + 1]) - 1;
}
