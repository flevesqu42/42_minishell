/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:54:27 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 11:00:36 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_sh *sh)
{
	sh->history = NULL;
	if (!(sh->line = ft_strnew(sizeof(char) * sh->size + 1)))
		sh_error(MALLOC_ERROR, INTERNAL, sh->name);
	while (42)
	{
		sh->history_ptr = sh->history;
		sh->line[0] = '\0';
		sh->index = 0;
		sh->last_newline = 0;
		get_prompt(sh);
		run_line_loop(sh);
		if (!ft_isstrspaces(sh->line))
			ft_blstpushnew(&sh->history, ft_strndup(sh->line
				, ft_strlen(sh->line) - 1));
		get_command_from_line(sh, sh->line);
	}
}
