/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 05:58:54 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/25 10:14:51 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_variable(t_sh *sh, char **line)
{
	size_t	index;
	char	save;
	char	*env;

	index = 1;
	while (ft_isalnum((*line)[index]) || (*line)[index] == '_')
		++index;
	save = (*line)[index];
	(*line)[index] = '\0';
	if ((env = ft_getenv(sh->env, (*line + 1))))
	{
		(*line)[index] = save;
		replace_sequence(sh, line, index, env);
	}
	else if (save == '?')
		replace_sequence(sh, line, 2, sh->ret);
	else
	{
		(*line)[index] = save;
		ft_memmove(*line, *line + index, ft_strlen(*line + index) + 1);
		*line -= 1;
	}
}

static int	check_specials_chars(char **line, size_t *index, t_sh *sh)
{
	if (**line == '\\')
	{
		ft_memmove(*line, *line + 1, ft_strlen(*line));
		if (ft_isspace(**line) && !(sh->flags & (DOUBLE_QUOTE | SIMPLE_QUOTE)))
			**line = 1;
	}
	if (**line == '$' && ft_isprint(*(*line + 1)))
	{
		check_variable(sh, line);
		sh->cmd[*index - 1] += (unsigned long long)sh->line;
		if (!*sh->cmd[*index - 1] || *sh->cmd[*index - 1] == ';'
				|| (ft_isspace(*sh->cmd[*index - 1]) && !(sh->flags & QUOTES)))
			sh->cmd[(*index -= 1)] -= (unsigned long long)sh->line;
		else
			sh->cmd[*index - 1] -= (unsigned long long)sh->line;
	}
	else if (!(sh->flags & QUOTES) && **line == ';')
	{
		**line = '\0';
		line_treatment(sh, *index);
		*index = 0;
		return ((int)(*line += 1));
	}
	*line += 1;
	return (0);
}

int			parse_chars(t_sh *sh, char **line, size_t *index)
{
	**line == '\\' ? (sh->flags |= BACKSLASH) : (sh->flags &= ~(BACKSLASH));
	if (**line == '\"' && !(sh->flags & SIMPLE_QUOTE))
	{
		sh->flags ^= DOUBLE_QUOTE;
		ft_memmove(*line, *line + 1, ft_strlen(*line));
	}
	else if (**line == '\'' && !(sh->flags & DOUBLE_QUOTE))
	{
		sh->flags ^= SIMPLE_QUOTE;
		ft_memmove(*line, *line + 1, ft_strlen(*line));
	}
	else if (!(sh->flags & SIMPLE_QUOTE))
		return (check_specials_chars(line, index, sh));
	else
		*line += 1;
	return (0);
}
