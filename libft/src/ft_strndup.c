/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 21:26:53 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 11:51:50 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*new;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(new, s1, len);
	new[len] = '\0';
	return (new);
}
