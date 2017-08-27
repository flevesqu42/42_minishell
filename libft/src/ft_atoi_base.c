/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:06:20 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 21:09:27 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_base(const char *str, int base)
{
	while (ft_isspace(*str))
		str += 1;
	if (base == 10 && *str == '-')
		return (-ft_atou_base(str + 1, base));
	return (ft_atou_base(str, base));
}
