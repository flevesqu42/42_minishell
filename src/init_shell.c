/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 00:13:32 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/28 08:30:56 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_termios(t_sh *sh)
{
	if (tgetent(NULL, ft_getenv(sh->env, "TERM")) <= 0)
		if (tgetent(NULL, "xterm-256color") <= 0)
			sh_error(GETATTR_ERROR, INTERNAL, sh);
	if (tcgetattr(0, &sh->old_terms) < 0)
		sh_error(GETATTR_ERROR, INTERNAL, sh);
	sh->my_terms = sh->old_terms;
	sh->my_terms.c_lflag &= ~(ICANON | ECHO);
	sh->my_terms.c_cc[VMIN] = 1;
	sh->my_terms.c_cc[VTIME] = 0;
	sh->my_terms.c_cc[VINTR] = 0;
	sh->old_terms.c_cc[VINTR] = 3;
}

void		init_shell(t_sh *sh, char **env)
{
	char			*shlvl;
	char			buf[11];

	sh->flags = 0;
	sh->env = NULL;
	sh->name = "minishell";
	sh->size = LINE_SIZE;
	ft_utoabuf(0, sh->ret);
	new_env(&sh->env, env, sh);
	if ((shlvl = ft_getenv(sh->env, "SHLVL")))
		push_to_env(&sh->env, "SHLVL", ft_utoabuf(ft_atoi(shlvl) < 0 ? 0
			: ft_atoi(shlvl) + 1, buf), sh);
	else
		push_to_env(&sh->env, "SHLVL", "1", sh);
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	init_termios(sh);
}
