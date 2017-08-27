/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_from_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 06:03:55 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/26 02:31:06 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*push_newline(t_sh *sh)
{
	size_t	diff;

	diff = ft_strlen(sh->line);
	ft_putstr_fd("\e[38;5;208m\\ \e[0m", 0);
	sh->cursor[1] += 1;
	sh->cursor[0] = 2;
	if (!(sh->flags & LINE_MULTIPLE))
		sh->index -= 1;
	sh->flags |= LINE_MULTIPLE;
	run_line_loop(sh);
	return (sh->line + diff);
}

static int	set_tilde(t_sh *sh, char *line)
{
	char	*home;

	if ((home = ft_getenv(sh->env, "HOME")))
		replace_sequence(sh, &line, 1, home);
	else
	{
		env_error("HOME", INTERNAL, sh->name);
		return (1);
	}
	return (0);
}

static int	set_new_argument(t_sh *sh, char *line, size_t *index)
{
	sh->cmd[*index] = (char*)(line - sh->line);
	if (*line == '~' && set_tilde(sh, line))
		return (1);
	*index += 1;
	return (0);
}

static void	split_arguments(t_sh *sh, char *line)
{
	size_t	index;

	index = 0;
	while (*line)
	{
		if (index >= ARG_MAX)
			sh_error(TOO_MUCH_ARG, INTERNAL, sh->name);
		if (!(sh->flags & QUOTES))
			erase_spaces(&line);
		if (!*line)
			break ;
		if (*line != ';' && !(sh->flags & (QUOTES)))
			if (set_new_argument(sh, line, &index))
				return ;
		while (*line && (!ft_isspace(*line) || (sh->flags & QUOTES)))
			if (parse_chars(sh, &line, &index))
				break ;
		if (!*line && (sh->flags & QUOTES))
			line = push_newline(sh);
	}
	line_treatment(sh, index);
}

void		get_command_from_line(t_sh *sh, char *line)
{
	char	*cmd[ARG_MAX];

	cmd[0] = NULL;
	sh->flags = 0;
	sh->cmd = cmd;
	split_arguments(sh, line);
}
