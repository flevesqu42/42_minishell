/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_treatment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 21:16:25 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/12 10:37:22 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_a_builtin(t_sh *sh, char **cmd)
{
	int		ret;

	ret = 0;
	if (!ft_strcmp(*cmd, "exit") && (ret = 1))
		exit_shell();
	else if (!ft_strcmp(*cmd, "env") && (ret = 1))
		env_built(sh, cmd);
	else if (!ft_strcmp(*cmd, "setenv") && (ret = 1))
		set_env_built(sh, cmd);
	else if (!ft_strcmp(*cmd, "unsetenv") && (ret = 1))
		unset_env_built(sh, &cmd[1]);
	else if (!ft_strcmp(*cmd, "getenv") && (ret = 1))
		ft_putendl(ft_getenv(sh->env, cmd[1]));
	else if (!ft_strcmp(*cmd, "echo") && (ret = 1))
		echo_built(&cmd[1]);
	else if (!ft_strcmp(*cmd, "cd") && (ret = 1))
		change_directory(sh, cmd[1]);
	return (ret);
}

void	check_variable(t_sh *sh, char **line)
{
	size_t	index;
	int		flag;
	char	*env;

	index = 1;
	while ((*line)[index] && !ft_isspace((*line)[index]))
		++index;
	flag = (*line)[index] ? 1 : 0;
	(*line)[index] = '\0';
	if ((env = ft_getenv(sh->env, (*line + 1))))
	{
		if (flag)
			(*line)[index] = ' ';
		ft_memmove(*line + index + ft_strlen(env), *line + index
			, ft_strlen(*line + index) + 1);
		ft_memmove(*line + index, env, ft_strlen(env));
		ft_memmove(*line, *line + index, ft_strlen(*line + index) + 1);
	}
	else
	{
		if (flag)
			(*line)[index] = ' ';
		ft_memmove(*line, *line + index, ft_strlen(*line + index) + 1);
	}
	*line += index;
}

int		parse_line(char **line, char **cmd, size_t *index, t_sh *sh)
{
	if (**line == '\\')
		ft_memmove(*line, &(*line)[1], ft_strlen(&(*line)[1]) + 1);
	else if (**line == ';')
	{
		**line = '\0';
		cmd[*index] = NULL;
		treat_command(sh, cmd);
		*index = 0;
		*line += 1;
		return (1);
	}
	else if (**line == '$')
		check_variable(sh, line);
	*line += 1;
	return (0);
}

void	split_line(char **cmd, char *line, t_sh *sh)
{
	size_t	index;
	int		ret;

	index = 0;
	while (*line)
	{
		while (ft_isspace(*line))
		{
			*line = '\0';
			line += 1;
		}
		if (*line)
		{
			if (*line != ';')
			{
				cmd[index] = line;
				index += 1;
			}
			while (*line && !ft_isspace(*line))
				if ((ret = parse_line(&line, cmd, &index, sh)))
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
	split_line(cmd, line, sh);
	if (!*cmd)
		return ;
	treat_command(sh, cmd);
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
