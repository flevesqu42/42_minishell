/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 04:13:31 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/20 04:13:36 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unsetenv(t_sh *sh, char **cmd)
{
	size_t	index;

	index = 0;
	if (!*cmd)
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
	while (cmd[index])
	{
		unset_env(&sh->env, cmd[index]);
		++index;
	}
}
