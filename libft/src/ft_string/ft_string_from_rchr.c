/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_from_rchr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 01:48:57 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/27 01:21:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

t_string	ft_string_from_rchr(t_string *initial, char to_search)
{
	size_t	index;

	if (!initial->len)
		return (*initial);
	index = initial->len - 1;
	while (index)
	{
		if (initial->string[index] == to_search)
		{
			return (ft_string_new(initial->string + index
				, initial->len - index));
		}
		--index;
	}
	return (*initial);
}
