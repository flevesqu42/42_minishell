/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 22:34:06 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 05:20:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n)
	{
		((unsigned char*)dst)[counter] = ((unsigned char*)src)[counter];
		if (((unsigned char*)src)[counter] == (unsigned char)c)
			return (&(((unsigned char*)dst)[counter + 1]));
		counter++;
	}
	return (NULL);
}
