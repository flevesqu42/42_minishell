/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 05:56:32 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/07 05:57:21 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_cursor_to(int *cursor)
{
	tputs(tgoto(tgetstr("cm", NULL), cursor[0], cursor[1]), 0, ft_putc);
}

void	put_term_string(char *str)
{
	tputs(tgetstr(str, NULL), 0, ft_putc);
}
