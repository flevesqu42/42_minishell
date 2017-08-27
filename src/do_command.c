/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 00:44:09 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/19 00:44:15 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_command(t_sh *sh, char **cmd)
{
	if (!*cmd)
		return ;
	else if (is_a_builtin(sh, cmd))
		return ;
	else if (is_a_bin(sh, cmd))
		return ;
	else if (**cmd == '/' || **cmd == '.')
		is_an_exec(sh, cmd, *cmd);
	else
		sh_error(CMD_NOT_FOUND, *cmd, sh->name);
}
