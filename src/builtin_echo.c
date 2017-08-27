/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 04:16:56 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/20 04:17:31 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo_numeric_input(char *str)
{
	size_t	index;

	index = 2;
	if (str[1] == '0')
	{
		str[0] = ft_atoi_base(&str[2], 8);
		while (str[index] >= '0' && str[index] <= '7')
			++index;
		ft_memmove(&str[1], &str[index], ft_strlen(&str[index]) + 1);
	}
	else if (str[1] == 'x')
	{
		str[0] = ft_atoi_base(&str[2], 16);
		ft_putnbr_fd(str[0], 3);
		ft_putchar_fd('\n', 3);
		while ((str[index] >= '0' && str[index] <= '9')
				|| (str[index] >= 'A' && str[index] <= 'F')
				|| (str[index] >= 'a' && str[index] <= 'f'))
			++index;
		ft_memmove(&str[1], &str[index], ft_strlen(&str[index]) + 1);
	}
}

static void	echo_char_sequence(char *str)
{
	if (str[1] == 'a' || str[1] == 'b' || str[1] == 'f' || str[1] == 'n'
			|| str[1] == 'r' || str[1] == 't' || str[1] == 'v')
	{
		if (str[1] == 'a')
			str[0] = '\a';
		if (str[1] == 'b')
			str[0] = '\b';
		if (str[1] == 'f')
			str[0] = '\f';
		if (str[1] == 'n')
			str[0] = '\n';
		if (str[1] == 'r')
			str[0] = '\r';
		if (str[1] == 't')
			str[0] = '\t';
		if (str[1] == 'v')
			str[0] = '\v';
		ft_memmove(&str[1], &str[2], ft_strlen(&str[2]) + 1);
	}
	else if (str[1] == '0' || str[1] == 'x')
		echo_numeric_input(str);
	else if (str[1] == '\\')
		ft_memmove(&str[0], &str[1], ft_strlen(&str[1]) + 1);
}

void		builtin_echo(char **cmd)
{
	size_t	index[2];

	index[0] = 0;
	while (cmd[index[0]])
	{
		index[1] = 0;
		if (index[0])
			ft_putchar(' ');
		while (cmd[index[0]][index[1]])
		{
			if (cmd[index[0]][index[1]] == '\\' && cmd[index[0]][index[1] + 1])
			{
				if (cmd[index[0]][index[1]] == 'c')
				{
					ft_putstr(cmd[index[0]]);
					return ;
				}
				echo_char_sequence(&cmd[index[0]][index[1]]);
			}
			++index[1];
		}
		ft_putstr(cmd[index[0]]);
		++index[0];
	}
	ft_putchar('\n');
}
