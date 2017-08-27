/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 03:00:02 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/27 06:21:33 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	autocomplete(t_sh *sh)
{
	t_string	word;

	word = ft_string_new(sh->line, sh->index);
	word = ft_string_from_rchr(&word, ' ');
	if (word.string != sh->line)
	{
		ft_string_offset(&word, +1);
		autocomplete_parse_path(sh, &word);
	}
	else if (word.string[0] == '.' || word.string[0] == '/')
		autocomplete_parse_path(sh, &word);
	else
		autocomplete_parse_binary(sh, &word);
}
