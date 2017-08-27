/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 01:49:33 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/25 04:10:24 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_dlstfree(t_dlist *lst)
{
	if (lst)
	{
		if (lst->content)
			free(lst->content);
		if (lst->next)
			ft_dlstfree(lst->next);
		free(lst);
		lst = NULL;
	}
}
