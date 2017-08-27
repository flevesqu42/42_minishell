/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoabuf_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 22:10:21 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 22:11:57 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_utoabuf_base(unsigned int nb, char *buf, int base)
{
	size_t	len;

	len = ft_ulen_base(nb, base);
	buf = buf + len;
	*buf = '\0';
	while (len--)
	{
		*(--buf) = nb % base + '0';
		nb /= base;
	}
	return (buf);
}
