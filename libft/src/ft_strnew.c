/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:58:16 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/23 12:04:18 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;

	++size;
	if (!(new = (char*)malloc(sizeof(char) * (size))))
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
