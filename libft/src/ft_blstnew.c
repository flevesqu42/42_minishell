/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 03:48:22 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 07:14:40 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_blist	*ft_blstpushnew(t_blist **first, void *data)
{
	t_blist	*new;

	if (!(new = (t_blist*)malloc(sizeof(t_blist))))
		return (NULL);
	new->data = data;
	if ((new->next = *first))
		new->next->prev = new;
	new->prev = NULL;
	*first = new;
	return (new);
}

t_blist	*ft_blstnew(void *data)
{
	t_blist	*new;

	if (!(new = (t_blist*)malloc(sizeof(t_blist))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
