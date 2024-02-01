/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:08:48 by moel-gha          #+#    #+#             */
/*   Updated: 2024/01/27 13:08:56 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**spcel_cmd;
	char	*path;

	if (ft_strlen(cmd) == 0)
		cmd = "cat";
	spcel_cmd = ft_split(cmd, ' ');
	path = get_path(spcel_cmd, env);
	if (execve(path, spcel_cmd, env) == -1)
	{
		write(2, "zsh: command not found: ", 25);
		write(2, spcel_cmd[0], ft_strlen(spcel_cmd[0]));
		write(2, "\n", 1);
		ft_free_all(spcel_cmd);
	}
}

void	child1(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening input file");
		exit(1);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("Error duplicating file descriptor for input file");
		exit(1);
	}
	if (dup2(p_fd[1], 1) == -1)
	{
		perror("Error duplicating file descriptor for pipe write end");
		exit(1);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	exec(av[2], env);
	exit(0);
}

void	child2(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening output file");
		exit(1);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("Error duplicating file descriptor for output file");
		exit(1);
	}
	if (dup2(p_fd[0], 0) == -1)
	{
		perror("Error duplicating file descriptor for pipe read end");
		exit(1);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	exec(av[3], env);
	exit(127);
}

void	child_processes(int ac, char **av, char **env, int *p_fd)
{
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		ft_error("./pipex infile cmd cmd outfile\n", 0);
	if (pipe(p_fd) == -1)
		ft_error("Error creating pipe", 1);
	pid1 = fork();
	if (pid1 == -1)
		ft_error("Error creating child process", 1);
	if (pid1 == 0)
		child1(av, p_fd, env);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_error("Error creating child2 process", 1);
		if (pid2 == 0)
			child2(av, p_fd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	p_fd[2];
	int	status;

	child_processes(ac, av, env, p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
			exit(WEXITSTATUS(status));
	}
	return (0);
}
