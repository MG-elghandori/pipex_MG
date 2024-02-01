/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:53:30 by moel-gha          #+#    #+#             */
/*   Updated: 2024/01/30 14:53:33 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check(char *cmd)
{
	write(2, "zsh: command not found: ", 25);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}

void	read_line(char *line, int *index)
{
	char	c;
	ssize_t	bytes;

	write(1, "pipe heredoc> ", 14);
	bytes = read(0, &c, 1);
	while (bytes > 0 && c != '\n')
	{
		line[*index] = c;
		(*index)++;
		bytes = read(0, &c, 1);
	}
	line[*index] = '\0';
}

void	write_line(int p_fd[2], char *line, int index)
{
	write(p_fd[1], line, index);
	write(p_fd[1], "\n", 1);
}

void	handle_here_doc(char *limiter, int *fd_input)
{
	char	line[1024];
	int		p_fd[2];
	int		index;

	index = 0;
	if (pipe(p_fd) == -1)
		exit(1);
	while (1)
	{
		read_line(line, &index);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		write_line(p_fd, line, index);
		index = 0;
	}
	close(p_fd[1]);
	*fd_input = p_fd[0];
}
