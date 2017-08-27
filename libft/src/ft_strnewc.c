/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 23:28:39 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 12:05:39 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnewc(size_t size, char c)
{
	char	*new;

	++size;
	if (!(new = (char*)malloc(sizeof(char) * (size))))
		return (NULL);
	ft_memset(new, c, size);
	return (new);
}
