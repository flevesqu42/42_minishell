/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:20:31 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 22:37:54 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	while (ft_isspace(*str))
		str += 1;
	if (str[0] == '0')
	{
		if (str[1] == 'x' || str[1] == 'X')
			return (ft_atou_base(str + 2, 16));
		else if (str[1] == 'b' || str[1] == 'B')
			return (ft_atou_base(str + 2, 2));
		else if (str[1] == '0')
			return (ft_atou_base(str + 2, 8));
		else
			return (ft_atou_base(str + 1, 10));
	}
	else
	{
		if (*str == '-')
			return (-ft_atou_base(str + 1, 10));
		else if (*str == '+')
			return (ft_atou_base(str + 1, 10));
		return (ft_atou_base(str, 10));
	}
}
