/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_heuristic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 06:24:55 by flevesqu          #+#    #+#             */
/*   Updated: 2017/05/29 06:26:26 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_heuristic	ft_new_heuristic(void *data, int heuristic)
{
	t_heuristic	new;

	new.data = data;
	new.heuristic = heuristic;
	return (new);
}
