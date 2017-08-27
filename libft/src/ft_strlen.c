/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:46:37 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 04:40:52 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef FAST_STRLEN

static inline size_t	strlen_byte(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return (ptr - str);
}

size_t					ft_strlen(const char *str)
{
	const t_ulong	*s;

	s = (t_ulong*)str;
	while (!LONGCHR_NULL(*s))
		++s;
	return (strlen_byte((const char*)s) + (const char*)s - str);
}

#else

size_t					ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return (ptr - str);
}

#endif
