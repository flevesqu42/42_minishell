/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 04:05:22 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 08:20:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_sh *sh)
{
	if (tcsetattr(0, TCSANOW, &sh->old_terms) < 0)
	{
		ft_putstr_fd(": cannot set termcaps attributes\n", 2);
		exit(1);
	}
	ft_putstr_fd("exit\n", 0);
	exit(0);
}
