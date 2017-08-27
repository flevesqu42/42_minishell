/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 03:48:22 by flevesqu          #+#    #+#             */
/*   Updated: 2017/06/01 05:03:06 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushnew(t_list **first, void *data)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->data = data;
	new->next = *first;
	*first = new;
	return (new);
}

t_list	*ft_lstnew(void *data)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->data = data;
	new->next = NULL;
	return (new);
}
