/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/10 10:43:58 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process(char *lstcmd, char **env)
{
	char	*cmd;
	char	**split_cmd;
	char	*path;
	int		ret;

	cmd = first_word(lstcmd);
	split_cmd = ft_split(lstcmd, ' ');
	path = extract_path(cmd, env);
	ret = execve(path, split_cmd, env);
	if (ret == -1)
	{
		ft_putstr_fd("Error : processus cannot be executed", 2);
		ft_free(split_cmd);
		free(cmd);
		free(path);
		exit(0);
		return (1);
	}
	return (0);
}

int	temp(char **argv, int *fd_pipe, char **env)
{
	int	fd_in;
	int	ret;
	int	err1;
	int	err2;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		return (ft_error(4));
	err1 = dup2(fd_in, STDIN_FILENO);
	err2 = dup2(fd_pipe[1], STDOUT_FILENO);
	if ((err1 == -1) || (err2 == -1))
		return (ft_error(6));
	close(fd_pipe[0]);
	ret = process(argv[2], env);
	return (ret);
}

int	final(char **argv, int *fd_pipe, char **env)
{
	int	fd_out;
	int	ret;
	int	err1;
	int	err2;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd_out == -1)
		return (ft_error(5));
	err1 = dup2(fd_out, STDOUT_FILENO);
	err2 = dup2(fd_pipe[0], STDIN_FILENO);
	if ((err1 == -1) || (err2 == -1))
		return (ft_error(6));
	close(fd_pipe[1]);
	ret = process(argv[3], env);
	return (ret);
}

int	ft_error(int	id)
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
		ft_putstr_fd("Error : pipe creation failed", 2);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_pipe[2];
	pid_t	id;
	int		ind;
	int		err;

	if (argc != 5)
		return (ft_error(1));
	ind = pipe(fd_pipe);
	if (ind == -1)
		exit(-1);
	id = fork();
	if (id == -1)
		exit(-1);
	if (id == 0)
		err = temp(argv, fd_pipe, env);
	if (err == -1)
		return (ft_error(2));
	err = final(argv, fd_pipe, env);
	if (err == -1)
		return (ft_error(3));
}

