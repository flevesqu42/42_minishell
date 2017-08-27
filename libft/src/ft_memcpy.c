/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 20:53:54 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/31 04:49:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_ulong			*d1;
	t_ulong			*s1;
	unsigned char	*s2;
	unsigned char	*d2;
	size_t			m;

	m = n >> 3;
	n &= 0x7;
	s1 = (t_ulong*)src;
	d1 = (t_ulong*)dst;
	s2 = (unsigned char*)&s1[m];
	d2 = (unsigned char*)&d1[m];
	while (m--)
		*(d1++) = *(s1++);
	while (n--)
		*(d2++) = *(s2++);
	return (dst);
}
