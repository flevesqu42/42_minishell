/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 04:10:27 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 04:43:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_setenv(t_sh *sh, char **cmd)
{
	size_t index;

	index = 0;
	if (!cmd[1])
		display_env(sh->env);
	else if (cmd[1] && cmd[2] && cmd[3])
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else if (!ft_isalpha(*cmd[1]) && *cmd[1] != '_')
		sh_error(FIRST_LETTER_ERROR, "setenv", sh);
	else
	{
		while (ft_isalnum(cmd[1][index]) || cmd[1][index] == '_')
			++index;
		if (cmd[1][index])
			sh_error(ALNUM_ERROR, "setenv", sh);
		else
			push_to_env(&sh->env, cmd[1], cmd[2], sh);
	}
}
