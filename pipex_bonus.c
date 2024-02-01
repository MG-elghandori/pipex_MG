/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:05:47 by moel-gha          #+#    #+#             */
/*   Updated: 2024/01/29 19:05:52 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_process(char *cmd, int fd, char **env, int input)
{
	pid_t	pid;
	char	**args;
	char	*path;

	if (ft_strlen(cmd) == 0)
		cmd = "cat";
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (dup2(fd, 1) == -1)
			exit(1);
		if (dup2(input, 0) == -1)
			exit(1);
		args = ft_split(cmd, ' ');
		path = get_path(args, env);
		if (execve(path, args, env) == -1)
			ft_check(cmd);
		exit(0);
	}
	close(fd);
}

int	check_args(int args)
{
	if (args < 5)
	{
		write(2, "./pipex infile cmd1 cmd2 ... cmdn outfile\n", 41);
		return (1);
	}
	return (0);
}

void	wait_for_children(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
			exit(WEXITSTATUS(status));
	}
}

int	handle_input(char **av)
{
	int (fd_input), (i);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		handle_here_doc(av[2], &fd_input);
		i = 2;
	}
	else
	{
		fd_input = ft_input(av[1]);
		i = 1;
	}
	if (dup2(fd_input, 0) == -1)
		exit(1);
	return (i);
}

int	main(int ac, char **av, char **env)
{
	int	p_fd[2];

	int (fd_out), (fd_input), (i);
	check_args(ac);
	i = handle_input(av);
	if (i == 2)
		fd_out = ft_output(av[ac - 1], O_APPEND);
	else
		fd_out = ft_output(av[ac - 1], O_TRUNC);
	while (++i < ac - 1)
	{
		if (pipe(p_fd) == -1)
			return (1);
		if (i + 1 == ac - 1)
			ft_process(av[i], fd_out, env, fd_input);
		else
			ft_process(av[i], p_fd[1], env, fd_input);
		fd_input = p_fd[0];
		close(p_fd[1]);
	}
	close(fd_input);
	wait_for_children();
	return (0);
}
