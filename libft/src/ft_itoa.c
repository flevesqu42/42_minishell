/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 05:17:57 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 22:30:01 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int i)
{
	char	*buf;

	if (!(buf = (char*)malloc(sizeof(char) * (ft_ilen(i) + 1))))
		return (NULL);
	if (i < 0)
	{
		*buf = '-';
		return (ft_utoabuf_base(-i, buf + 1, 10) - 1);
	}
	else
		return (ft_utoabuf_base(i, buf, 10));
}
