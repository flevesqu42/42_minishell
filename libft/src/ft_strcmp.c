/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 21:40:45 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 08:30:08 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_nocase(const char *s1, const char *s2)
{
	while (*s1)
	{
		if (ft_tolower(*s1) ^ ft_tolower(*s2))
			return ((t_uchar)ft_tolower(*s1) - (t_uchar)ft_tolower(*s2));
		++s1;
		++s2;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

int	ft_strcmp(const char *src1, const char *src2)
{
	return (ft_memcmp(src1, src2, ft_strlen(src1) + 1));
}
