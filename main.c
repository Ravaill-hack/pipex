/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/09 20:11:15 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process(char *lstcmd, char **env)
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
		//ft_error2(cmd);
		free(cmd);
		exit(0);
	}
}

void	temp(char **argv, int *fd_pipe, char **env)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in,	STDIN_FILENO);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[0]);
	process(argv[2], env);
}

void	final(char **argv, int *fd_pipe, char **env)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	process(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_pipe[2];
	pid_t	id;
	int		ind;

	if (argc != 5)
	{
		//ft_error1();
		return (1);
	}
	ind = pipe(fd_pipe);
	if (ind == -1)
		exit(-1);
	id = fork();
	if (id == -1)
		exit(-1);
	if (id == 0)
		temp(argv, fd_pipe, env);
	final(argv, fd_pipe, env);
}
