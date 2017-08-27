/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 07:56:42 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 10:14:51 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_treatment(t_sh *sh, size_t index)
{
	char	*line;

	sh->cmd[index] = NULL;
	while (index--)
		sh->cmd[index] += (unsigned long long)sh->line;
	line = sh->cmd[0] ? sh->cmd[0] : sh->line;
	while (*line)
	{
		if (*line == 1)
			*line = '\0';
		line += 1;
	}
	if (*sh->cmd)
		do_command(sh, sh->cmd);
}
