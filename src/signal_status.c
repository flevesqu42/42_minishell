/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 10:54:20 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 10:55:10 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signal_status(int stat, char *cmd, pid_t pid)
{
	int	tmp;

	if ((tmp = WTERMSIG(stat)) == SIGSEGV || tmp == SIGBUS || tmp == SIGQUIT)
		display_sig_error(stat, cmd, pid);
}
