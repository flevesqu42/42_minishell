/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 01:07:03 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/15 08:52:16 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char ***tab)
{
	size_t	index;

	index = 0;
	if (!(*tab))
		return ;
	while ((*tab)[index])
	{
		free((*tab)[index]);
		(*tab)[index] = NULL;
		++index;
	}
	free((*tab));
	tab = NULL;
}
