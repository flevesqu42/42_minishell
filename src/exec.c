/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 22:59:57 by flevesqu          #+#    #+#             */
/*   Updated: 2016/12/12 10:36:28 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_an_exec(t_sh *sh, char **cmd, char *path)
{
	struct stat	infos;

	if (lstat(path, &infos) < 0)
		sh_error(NO_FILE, *cmd, sh->name);
	else if ((infos.st_mode & S_IFDIR))
		sh_error(IS_A_DIRECTORY, *cmd, sh->name);
	else if (!(infos.st_mode & S_IXUSR))
		sh_error(NO_RIGHT, *cmd, sh->name);
	else
		execute_command(sh, cmd, path);
}

void	execute_command(t_sh *sh, char **cmd, char *path)
{
	pid_t	pid;

	push_to_env(&sh->env, "_", path);
	if ((pid = fork()) < 0)
		sh_error(FORK_ERROR, *cmd, sh->name);
	else if (pid == 0)
		execve(path, cmd, sh->env);
	else
		waitpid(-1, NULL, 0);
}

int		check_in_directory(t_sh *sh, char **cmd, char *path)
{
	DIR		*dir;
	struct dirent   *dirent;

	if (!(dir = opendir(path)))
		return (0);
	while ((dirent = readdir(dir)))
		if (!ft_strcmp(*cmd, dirent->d_name))
		{
			ft_strcat(path, "/");
			ft_strcat(path, dirent->d_name);
			is_an_exec(sh, cmd, path);
			closedir(dir);
			return (1);
		}
	closedir(dir);
	return (0);
}

int		get_path(char **env_path, char *path)
{
	if (!*env_path || !**env_path)
		return (0);
	if (ft_strchr(*env_path, ':'))
	{
		ft_strncpy(path, *env_path, ft_strchr(*env_path, ':') - *env_path);
		path[ft_strchr(*env_path, ':') - *env_path] = '\0';
		*env_path += ft_strlen(path) + 1;
		return (1);
	}
	else
	{
		ft_strcpy(path, *env_path);
		*env_path += ft_strlen(path);
		return (1);
	}
}

int		is_a_bin(t_sh *sh, char **cmd)
{
	char	path[PATH_MAX];
	char	*env_path;

	if (!(env_path = ft_getenv(sh->env, "PATH")))
		return (0);
	while (get_path(&env_path, path))
		if (check_in_directory(sh, cmd, path))
			return (1);
	return (0);
}
