/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 01:42:35 by flevesqu          #+#    #+#             */
/*   Updated: 2017/07/30 21:14:45 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H
# include <string.h>

typedef struct	s_string
{
	char	*string;
	size_t	len;
}				t_string;

t_string		ft_string_new(char *str, size_t size);
void			ft_string_offset(t_string *pstr, int off);
t_string		ft_string_from_chr(t_string *initial, char to_search);
t_string		ft_string_from_rchr(t_string *initial, char to_search);

#endif
