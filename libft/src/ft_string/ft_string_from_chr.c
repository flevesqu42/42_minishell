/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_from_chr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 01:47:21 by flevesqu          #+#    #+#             */
/*   Updated: 2017/05/26 21:36:59 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

t_string	ft_string_from_chr(t_string *initial, char to_search)
{
	size_t	index;

	index = 0;
	while (index < initial->len)
	{
		if (initial->string[index] == to_search)
		{
			return (ft_string_new(initial->string + index
				, initial->len - index));
		}
		++index;
	}
	return (*initial);
}
