/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:11:12 by moel-gha          #+#    #+#             */
/*   Updated: 2024/01/27 13:11:15 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *error_message, int flg)
{
	if (flg == 0)
	{
		write(2, "./pipex infile cmd cmd outfile\n", 30);
		exit(EXIT_FAILURE);
	}
	write(2, error_message, ft_strlen(error_message));
	exit(EXIT_FAILURE);
}

void	ft_free_all(char **f)
{
	size_t	i;

	i = 0;
	while (f[i])
	{
		free(f[i]);
		i++;
	}
	free(f);
}

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_exec_path(char *path, char *cmd)
{
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin(path, "/");
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(exec, F_OK | X_OK) == 0)
		return (exec);
	else
	{
		free(exec);
		return (NULL);
	}
}

char	*get_path(char **spcel_cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;

	if (ft_strchr(spcel_cmd[0], '/'))
		return (spcel_cmd[0]);
	i = -1;
	allpath = ft_split(get_env("PATH", env), ':');
	if (allpath)
	{
		while (allpath[++i])
		{
			exec = get_exec_path(allpath[i], spcel_cmd[0]);
			if (exec != NULL)
			{
				ft_free_all(allpath);
				return (exec);
			}
		}
		ft_free_all(allpath);
	}
	return (spcel_cmd[0]);
}
