/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 07:21:26 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/07 07:54:39 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_getenv(char **env, char *toget)
{
	size_t	size[2];

    if (!toget)
        return (NULL);
	size[0] = ft_strlen(toget);
    while (*env)
    {
        if ((size[1] = ft_strchr(*env, '=') - *env) == size[0]
				&& !ft_strncmp(toget, *env, size[1]))
            return (ft_strchr(*env, '=') + 1);
        env += 1;
    }
    return (NULL);
}
