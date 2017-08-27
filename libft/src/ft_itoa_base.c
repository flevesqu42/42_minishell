/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 22:17:40 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 22:43:30 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int i, int base)
{
	char	*buf;

	if (!(buf = (char*)malloc(sizeof(char) * (ft_ilen_base(i, base) + 1))))
		return (NULL);
	if (i < 0)
	{
		*buf = '-';
		return (ft_utoabuf_base(-i, buf + 1, base) - 1);
	}
	else
		return (ft_utoabuf_base(i, buf, base));
}
