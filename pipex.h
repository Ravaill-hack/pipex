/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:20:34 by lmatkows          #+#    #+#             */
/*   Updated: 2025/01/06 11:24:28 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	ft_free(char **str);
int		find_line(char *title, char **env);
char	*extract_env(char *title, char **env);
char	*extract_path(char *cmd, char **env);
int		ft_error(char *str);
void	close_2_fd(int fd_in, int fd_out);
void	close_all_fd(int fd_in, int fd_out, int fd[2]);
void	wait_for_all_pids(pid_t *id_cmd);

#endif