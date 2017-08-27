/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:13:28 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/24 11:11:29 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	t_ulong			*s1;
	unsigned char	*s2;
	size_t			m;

	s1 = s;
	m = n >> 3;
	s2 = (unsigned char*)&s1[m];
	n &= 0x7;
	while (m--)
		*(s1++) = '\0';
	while (n--)
		*(s2++) = '\0';
}
