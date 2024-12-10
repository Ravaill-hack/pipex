/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:58:14 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/10 11:25:56 by lmatkows         ###   ########.fr       */
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

int	ft_error(int id)
{
	if (id == 1)
		ft_putstr_fd("Error : incorrect number of arguments", 2);
	else if (id == 2)
		ft_putstr_fd("Error : cannot execute child process", 2);
	else if (id == 3)
		ft_putstr_fd("Error : cannot execute parent process", 2);
	else if (id == 4)
		ft_putstr_fd("Error : file cannot be opened", 2);
	else if (id == 5)
		ft_putstr_fd("Error : file cannot be written", 2);
	else if (id == 6)
		ft_putstr_fd("Error : pipe assignation failed", 2);
	else if (id == 7)
		ft_putstr_fd("Error : pipe creation failed", 2);
	else if (id == 8)
		ft_putstr_fd("Error : fork failed", 2);
	return (1);
}
