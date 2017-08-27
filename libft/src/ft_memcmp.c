/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 00:21:49 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/02 05:51:37 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	memcmp_byte(const t_uchar *s1, const t_uchar *s2, size_t n)
{
	while (n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1;
		++s2;
	}
	return (0);
}

int					ft_memcmp(const void *src1, const void *src2, size_t n)
{
	t_ulong		*s1;
	t_ulong		*s2;
	size_t		m;

	m = n >> 3;
	s1 = (t_ulong*)src1;
	s2 = (t_ulong*)src2;
	src1 = &s1[m];
	src2 = &s2[m];
	while (m--)
	{
		if (*s1 ^ *s2)
			return (memcmp_byte((const t_uchar*)s1, (const t_uchar*)s2, 8));
		++s1;
		++s2;
	}
	return (memcmp_byte((const t_uchar*)src1, (const t_uchar*)src2, n & 0x7));
}
