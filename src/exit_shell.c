/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 04:05:22 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/20 04:08:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_sh *sh)
{
	if (tcsetattr(0, TCSANOW, &sh->old_terms) < 0)
		sh_error(SETATTR_ERROR, INTERNAL, "minishell");
	ft_putstr_fd("exit\n", 0);
	exit(0);
}
