/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 08:35:51 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/26 04:05:42 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_prompt(t_sh *sh)
{
	char		*home;
	char		*wd;
	static char	prompt[PATH_MAX + 17];

	ft_strcpy(prompt, "\e[38;5;208mᐂ\e[90m [");
	wd = get_working_directory(sh);
	if ((home = ft_getenv(sh->env, "HOME")) && *home
		&& !ft_strncmp(wd, home, ft_strlen(home)))
	{
		*wd = '~';
		ft_strcpy(&wd[1], &wd[ft_strlen(home)]);
	}
	ft_strcat(prompt, wd);
	ft_strcat(prompt, "]\e[0m >_ ");
	ft_putstr_fd(prompt, 2);
}
