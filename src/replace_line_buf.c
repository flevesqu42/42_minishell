/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_line_buf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 00:56:08 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/19 00:56:13 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		replace_line_buf(t_sh *sh, size_t size)
{
	char	*new;

	if (size > sh->size)
	{
		sh->size = size;
		if (!(new = ft_strnew(sizeof(char) * sh->size + 1)))
			sh_error(MALLOC_ERROR, INTERNAL, sh);
		ft_memcpy(new, sh->line, size);
		free(sh->line);
		sh->line = new;
	}
}
