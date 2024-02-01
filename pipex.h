/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-gha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:17:55 by moel-gha          #+#    #+#             */
/*   Updated: 2024/01/27 13:17:58 by moel-gha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

size_t	ft_strlen(const char *theString);
void	ft_free_all(char **f);
char	*get_exec_path(char *path, char *cmd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2);
int		count_words(char const *s, char c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_str(char const *s, char c);
char	*get_env(char *name, char **env);
char	*get_path(char **spcel_cmd, char **env);
int		ft_error(char *error_message, int flg);
void	ft_check(char *cmd);
int		ft_output(char *av, int flag);
int		ft_input(char *av);
void	ft_process(char *cmd, int fd, char **env, int input);
int		check_args(int args);
void	wait_for_children(void);
void	handle_here_doc(char *limiter, int *fd_input);
void	read_line(char *line, int *index);
void	write_line(int p_fd[2], char *line, int index);

#endif
