/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:58:57 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 05:47:20 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void)ac;
	(void)av;
	DEBUG_INIT();
	DEBUG("Debug tty here:\n");
	init_shell(&sh, env);
	shell_loop(&sh);
	return (0);
}
