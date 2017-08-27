/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 02:51:39 by flevesqu          #+#    #+#             */
/*   Updated: 2016/11/26 02:55:32 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**alloc_wds(const char *s)
{
	char	**wds;
	size_t	len;

	len = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s += 1;
		if (*s)
			len++;
		while (!ft_isspace(*s) && *s)
			s += 1;
	}
	wds = (char**)malloc(sizeof(char*) * (len + 1));
	if (wds)
		wds[len] = NULL;
	return (wds);
}

char		**ft_splitwhitespaces(const char *s)
{
	char	**wds;
	size_t	index;
	size_t	wdi;
	size_t	chi;

	wdi = 0;
	index = 0;
	if (!s || !(wds = alloc_wds(s)))
		return (NULL);
	while (s[index])
	{
		chi = 0;
		while (ft_isspace(s[index]))
			index++;
		while (!ft_isspace(s[index + chi]) && s[index + chi])
			chi++;
		if (chi)
			wds[wdi] = ft_strsub(s, index, chi);
		wdi++;
		index += chi;
	}
	return (wds);
}
