/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 21:14:50 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/12 04:39:47 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_to_env(char ***env, char *key, char *value)
{
	size_t  i;
	size_t	size[2];

	i = 0;
	size[0] = ft_strlen(key);
	if (!value)
		value = "";
	while ((*env)[i] && !((size[1] = ft_strchr((*env)[i], '=') - (*env)[i])
			== size[0] && !ft_strncmp(key, (*env)[i], size[1])))
		++i;
	if ((*env)[i])
		free((*env)[i]);
	else
		new_env(&(*env), (*env));
	if (!((*env)[i] = (char*)malloc(sizeof(char)
		* (ft_strlen(value) + ft_strlen(key) + 2))))
		sh_error(MALLOC_ERROR, "internal error", "minishell");
	ft_strcpy((*env)[i], key);
	ft_strcat((*env)[i], "=");
	ft_strcat((*env)[i], value);
}

void	display_env(char **env)
{
	while (*env)
	{
		ft_putendl(*env);
		env += 1;
	}
}
void	new_env(char ***dst, char **src)
{
	size_t  size;
	char	**new;

	size = 0;
	while (src[size])
		++size;
	if (!(new = (char**)malloc(sizeof(char*) * (size + 2))))
		sh_error(MALLOC_ERROR, "internal error", "minishell");
	size = 0;
	while (src[size])
	{
		new[size] = ft_strdup(src[size]);
		if (*dst)
			free(src[size]);
		++size;
	}
	new[size] = NULL;
	new[size + 1] = NULL;
	if (*dst)
		free(src);
	*dst = new;
}

void	unset_env(char ***env, char *to_unset)
{
	size_t	i;
	size_t	size[2];

	i = 0;
	size[0] = ft_strlen(to_unset);
	while ((*env)[i] && !((size[1] = ft_strchr((*env)[i], '=') - (*env)[i])
			== size[0] && !ft_strncmp(to_unset, (*env)[i], size[1])))
		++i;
	free((*env)[i]);
	while ((*env)[i])
	{
		(*env)[i] = (*env)[i + 1];
		++i;
	}
}
