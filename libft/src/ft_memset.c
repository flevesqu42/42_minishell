/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:50:32 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/24 11:13:24 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	t_ulong			*s1;
	unsigned char	*s2;
	size_t			m;
	t_ulong			dc;

	s1 = s;
	m = n >> 3;
	s2 = (unsigned char*)&s1[m];
	n &= 0x7;
	dc = DUPC(c);
	while (m--)
		*(s1++) = dc;
	while (n--)
		*(s2++) = dc;
	return (s);
}
