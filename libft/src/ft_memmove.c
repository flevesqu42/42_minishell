/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 23:36:17 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/02 07:14:51 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	t_ulong	*s1;
	t_ulong	*d1;
	t_uchar	*s2;
	t_uchar	*d2;
	size_t	m;

	if (dst < src)
		return (ft_memcpy(dst, src, n));
	m = n >> 3;
	n &= 0x7;
	s1 = ((t_ulong*)src) + m;
	d1 = ((t_ulong*)dst) + m;
	s2 = ((t_uchar*)&src[m << 3]) + n;
	d2 = ((t_uchar*)&dst[m << 3]) + n;
	while (n--)
		*(--d2) = *(--s2);
	while (m--)
		*(--d1) = *(--s1);
	return (dst);
}
