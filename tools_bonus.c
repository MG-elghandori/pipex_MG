/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:06:04 by moel-gha          #+#    #+#             */
/*   Updated: 2024/01/29 19:06:07 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_output(char *av, int flag)
{
	int	fdout;

	fdout = open(av, O_WRONLY | O_CREAT | flag, 0644);
	if (fdout == -1)
		exit(1);
	return (fdout);
}

int	ft_input(char *av)
{
	int	fdin;

	fdin = open(av, O_RDONLY);
	if (fdin == -1)
	{
		perror(av);
		exit(1);
	}
	return (fdin);
}
