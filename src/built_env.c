/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 21:13:32 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/16 07:10:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			display_env_error(char opt)
{
	if (opt == 'u')
		ft_putendl_fd("env: option requires an argument -- u", 2);
	else
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(opt, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putendl_fd("env [-i] [-u name] [name=value]... [utility [argument...]]"
		, 2);
	return (-1);
}

void		env_built_post(char **cmd, t_sh *sh)
{
	char	*tmp;

	while (*cmd && **cmd != '=' && (tmp = ft_strchr(*cmd, '=')))
	{
		*tmp = '\0';
		push_to_env(&sh->env, *cmd, tmp + 1);
		cmd += 1;
	}
	if (*cmd)
		treat_command(sh, cmd);
	else
		display_env(sh->env);
}

void free_env(char **env)
{
	while (*env)
	{
		free(*env);
		*env = NULL;
		env += 1;
	}
}

int	env_built_options(t_sh *sh, char **cmd, size_t *i)
{
	while (cmd[i[0]][++i[1]])
		if (cmd[i[0]][i[1]] == 'u')
		{
			if (cmd[i[0]][i[1] + 1])
			{
				unset_env(&sh->env, &cmd[i[0]][i[1] + 1]);
				return (0);
			}
			else
			{
				if (!cmd[i[0] + 1])
					return (display_env_error('u'));
				unset_env(&sh->env, cmd[(i[0] += 1)]);
				return (0);
			}
		}
		else if (cmd[i[0]][i[1]] == 'i')
			free_env(sh->env);
		else if (cmd[i[0]][i[1]] != '-')
			return (display_env_error(cmd[i[0]][i[1]]));
	return (0);
}

void		env_built_bis(t_sh *sh, char **cmd)
{
	int		ret;
	size_t	index[2];

	index[0] = 0;
	while (cmd[index[0]] && *cmd[index[0]] == '-'
			&& ft_strcmp_nocase(cmd[index[0]], "--"))
	{
		index[1] = 0;
		if ((ret = env_built_options(sh, cmd, index)))
			if (ret < 0)
			 	return ;
		index[0] += 1;
	}
	env_built_post(&cmd[index[0]], sh);
}

void		env_built(t_sh *sh, char **cmd)
{
	t_sh	new;

	new = *sh;
	new.env = NULL;
	new.name = "env";
	new_env(&new.env, sh->env);
	env_built_bis(&new, cmd + 1);
	ft_free_2d(&new.env);
}
