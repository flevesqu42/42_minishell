/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:46:48 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 19:57:33 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*memory;

	if (!(memory = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	ft_bzero(memory, size);
	return (memory);
}
