/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 03:03:27 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/24 03:44:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	*memrchr_byte(unsigned char *s, size_t n, unsigned char c)
{
	s += 7;
	while (n--)
	{
		if (*s == c)
			return (s);
		--s;
	}
	return (NULL);
}

void				*ft_memrchr(const void *s, int c, size_t n)
{
	t_ulong			*s1;
	size_t			m;
	t_ulong			l;
	t_ulong			dc;

	m = n >> 3;
	s1 = (t_ulong*)((char*)s + n) - 1;
	s = &s1[-m];
	dc = DUPC(c);
	while (m--)
	{
		l = dc ^ *s1;
		if (LONGCHR_NULL(l))
			return (memrchr_byte((t_uchar*)s1, 8, c));
		--s1;
	}
	return (memrchr_byte((t_uchar*)s, n & 7, c));
}
