/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:15:02 by flevesqu          #+#    #+#             */
/*   Updated: 2015/12/14 01:04:09 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, t_dlist *(*f)(t_dlist *elem))
{
	t_dlist	*new;
	t_dlist	*link;
	t_dlist	*first;

	if (!f)
		return (NULL);
	new = (*f)(lst);
	first = ft_dlstnew(new->content, new->content_size);
	link = first;
	lst = lst->next;
	while (lst)
	{
		new = (*f)(lst);
		link->next = ft_dlstnew(new->content, new->content_size);
		link = link->next;
		lst = lst->next;
	}
	return (first);
}
