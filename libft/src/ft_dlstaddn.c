/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 01:21:17 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/30 01:35:19 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstaddn(t_dlist **lst, size_t n, t_dlist *new)
{
	*lst = ft_dlstgetn(lst, n);
	if (*lst)
	{
		new->next = (*lst)->next;
		(*lst)->next = new;
	}
}
