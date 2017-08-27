/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 22:06:17 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 08:33:09 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_nocase(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 && --n)
	{
		if (ft_tolower(*s1) ^ ft_tolower(*s2))
			return ((t_uchar)ft_tolower(*s1) - (t_uchar)ft_tolower(*s2));
		++s1;
		++s2;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = ft_strlen(s1) + 1;
	return (ft_memcmp(s1, s2, n < len ? n : len));
}
