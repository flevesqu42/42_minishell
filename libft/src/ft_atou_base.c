/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 20:35:28 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/31 07:54:14 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atou_base(const char *str, int base)
{
	unsigned int	result;

	result = 0;
	while (ft_isdigitbase(*str, base))
	{
		if (ft_isupper(*str))
			result = result * base + *str - 'A' + 10;
		else if (ft_islower(*str))
			result = result * base + *str - 'a' + 10;
		else
			result = result * base + *str - '0';
		str += 1;
	}
	return (result);
}
