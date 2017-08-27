/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ilen_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 21:48:29 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 21:49:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ilen_base(int i, int base)
{
	if (i < 0)
		return (ft_ulen_base(-i, base) + 1);
	return (ft_ulen_base(i, base));
}
