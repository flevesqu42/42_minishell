/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 23:56:42 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/24 04:40:07 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*ptr;

	if (!s || !(sub = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ptr = sub;
	s += start;
	while (len--)
		*(ptr++) = *(s++);
	*ptr = '\0';
	return (sub);
}
