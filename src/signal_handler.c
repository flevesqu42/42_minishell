/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 10:18:25 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 10:18:26 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int i)
{
	if (i == 2)
		ft_putchar_fd('\n', 0);
	else if (i == SIGQUIT)
		ft_putchar_fd(7, 0);
	else if (i == SIGWINCH)
		if (tgetent(NULL, "xterm-256color") <= 0)
			sh_error(GETATTR_ERROR, INTERNAL, "minishell");
}
