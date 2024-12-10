/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:58:14 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/10 16:44:47 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	res = ft_strjoin(temp, s3);
	free(temp);
	return (res);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_error(char *str)
{
	perror(str);
	return (-1);
}

void	close_2_fd(int fd_in, int fd_out)
{
	close(fd_in);
	close(fd_out);
}

void	close_all_fd(int fd_in, int fd_out, int *fd)
{
	int	i;

	i = 0;
	close(fd_in);
	close(fd_out);
	while (fd[i])
	{
		close(fd[i]);
		i++;
	}
}
