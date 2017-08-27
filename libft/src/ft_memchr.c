/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 00:21:49 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 12:11:54 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	*memchr_byte(unsigned char *s, size_t n, unsigned char c)
{
	while (n--)
	{
		if (*s == c)
			return (s);
		++s;
	}
	return (NULL);
}

void				*ft_memchr(const void *s, int c, size_t n)
{
	t_ulong			*s1;
	size_t			m;
	t_ulong			l;
	t_ulong			dc;

	m = n >> 3;
	s1 = (t_ulong*)s;
	s = &s1[m];
	dc = DUPC(c);
	while (m--)
	{
		l = dc ^ *s1;
		if (LONGCHR_NULL(l))
			return (memchr_byte((t_uchar*)s1, 8, c));
		++s1;
	}
	return (memchr_byte((t_uchar*)s, n & 7, c));
}
