/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 06:42:25 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/29 10:00:15 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_putchar_bis(char c)
{
	write(1, &c, 1);
}

void		ft_putchar(int i)
{
	if (i < 0x80)
		write(1, &i, 1);
	else if (i < 0x800)
	{
		ft_putchar_bis(i >> 6 | 0xC0);
		ft_putchar_bis((i & 0xBF) | 0x80);
	}
	else if (i < 0x10000)
	{
		ft_putchar_bis(i >> 12 | 0xE0);
		ft_putchar_bis(((i >> 6) & 0xBF) | 0x80);
		ft_putchar_bis((i & 0xBF) | 0x80);
	}
	else
	{
		ft_putchar_bis(i >> 18 | 0xF0);
		ft_putchar_bis(((i >> 12) & 0xBF) | 0x80);
		ft_putchar_bis(((i >> 6) & 0xBF) | 0x80);
		ft_putchar_bis((i & 0xBF) | 0x80);
	}
}
