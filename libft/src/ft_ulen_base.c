/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulen_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 21:43:09 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 21:51:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ulen_base(unsigned int i, int base)
{
	size_t	value;

	value = !i ? 1 : 0;
	while (i)
	{
		++value;
		i /= base;
	}
	return (value);
}
