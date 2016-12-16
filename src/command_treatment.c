/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_treatment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 21:16:25 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/16 06:28:00 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_variable(t_sh *sh, char **line)
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
		ft_memmove(*line + index + ft_strlen(env), *line + index
			, ft_strlen(*line + index) + 1);
		ft_memmove(*line + index, env, ft_strlen(env));
		ft_memmove(*line, *line + index, ft_strlen(*line + index) + 1);
		*line += ft_strlen(env) - 1;
	}
	else
	{
		(*line)[index] = save;
		ft_memmove(*line, *line + index, ft_strlen(*line + index) + 1);
		*line -= 1;
	}
}

int		check_specials_chars(char **line, char **cmd, size_t *index, t_sh *sh)
{
	if (**line == '\\')
		ft_memmove(*line, &(*line)[1], ft_strlen(&(*line)[1]) + 1);
	else if (**line == '$' && *(*line + 1))
	{
		check_variable(sh, line);
		if (!*cmd[*index - 1] || *cmd[*index - 1] == ';'
				|| (ft_isspace(*cmd[*index - 1]) && !(sh->flags & QUOTES)))
			--*index;
	}
	else if (!(sh->flags & QUOTES) && **line == ';')
	{
		**line = '\0';
		cmd[*index] = NULL;
		treat_command(sh, cmd);
		*index = 0;
		*line += 1;
		return (1);
	}
	*line += 1;
	return (0);
}

int		parse_chars(char **line, char **cmd, size_t *index, t_sh *sh)
{
	if (**line == '\"' && !(sh->flags & SIMPLE_QUOTE))
	{
		sh->flags ^= DOUBLE_QUOTE;
		ft_memmove(*line, &(*line)[1], ft_strlen(&(*line)[1]) + 1);
	}
	else if (**line == '\'' && !(sh->flags & DOUBLE_QUOTE))
	{
		sh->flags ^= SIMPLE_QUOTE;
		ft_memmove(*line, &(*line)[1], ft_strlen(&(*line)[1]) + 1);
	}
	else if (!(sh->flags & SIMPLE_QUOTE))
		return (check_specials_chars(line, cmd, index, sh));
	else
		*line += 1;
	return (0);
}


void erase_spaces(char **line)
{
	while (ft_isspace(**line))
	{
		**line = '\0';
		*line += 1;
	}
}
void	split_line(char **cmd, char *line, t_sh *sh)
{
	size_t	index;
	int		ret;

	index = 0;
	while (*line)
	{
		if (!(sh->flags & QUOTES))
			erase_spaces(&line);
		if (*line)
		{
			if (*line != ';' || (sh->flags & QUOTES))
			{
				cmd[index] = line;
				index += 1;
			}
			while (*line && (!ft_isspace(*line) || (sh->flags & QUOTES)))
				if ((ret = parse_chars(&line, cmd, &index, sh)))
				{
					if (ret < 0)
						return ;
					break ;
				}
		}
	}
	cmd[index] = NULL;
}

void	treat_line(t_sh *sh, char *line)
{
	char	*cmd[ARG_MAX];

	cmd[0] = NULL;
	sh->flags = 0;
	split_line(cmd, line, sh);
	if (!*cmd)
		return ;
	treat_command(sh, cmd);
	sh->flags = 0;
}

void	treat_command(t_sh *sh, char **cmd)
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
