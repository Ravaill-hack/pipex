/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/03 09:39:42 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_all_pids(pid_t *id_cmd)
{
	waitpid(id_cmd[0], NULL, 0);
	waitpid(id_cmd[1], NULL, 0);
}

void	exec_cmd(char *lstcmd, char **env, int fd_in, int fd_out)
{
	char	**split_cmd;
	char	*path;
	int		err;

	if (dup2(fd_in, STDIN_FILENO) == -1)
		perror("Error : fd_in assignation failed");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("Error : fd_out assignation failed");
	close_2_fd(fd_in, fd_out);
	split_cmd = ft_split(lstcmd, ' ');
	path = extract_path(split_cmd[0], env);
	err = execve(path, split_cmd, env);
	if (err == -1)
	{
		perror("Error : processus cannot be executed");
		ft_free(split_cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
}

pid_t	exec_cmds(int fd_in_out[2], int argc, char **argv, char **env)
{
	int		fd_pipe[argc - 4][2];
	pid_t	id_cmd[argc - 3];
	int		i;

	while (i <= argc - 4)
	{
		if (pipe(fd_pipe[i]) == -1)
			return (ft_error("Error : pipe creation failed"));
		id_cmd[i] = fork();
		if (id_cmd[i] == -1)
			return (ft_error("Error : fork execution failed"));
		close(fd_pipe[i][0]);
		if (id_cmd[i] == 0 && i == 0)
			exec_cmd(argv[2], env, fd_in_out[0], fd_pipe[i][1]);
		else if (id_cmd[i] == 0 && i > 0)
		{
			close(fd_pipe[i - 1][0]);
			exec_cmd(argv[2], env, fd_pipe[i - 1][0], fd_pipe[i][1]);
		}
		id_cmd[i + 1] = fork();
		if (id_cmd[i + 1] == -1)
				return (ft_error("Error : fork execution failed"));
		close(fd_pipe[i][1]);
		if (i < argc - 4 && id_cmd[i + 1] == 0)
		{
			if (pipe(fd_pipe[i + 1]) == -1)
				return (ft_error("Error : pipe creation failed"));
			close(fd_pipe[i + 1][0]);
			exec_cmd(argv[3], env, fd_pipe[i][0], fd_pipe[i + 1][1]);
		}
		else if (i == argc - 4)
			exec_cmd(argv[3], env, fd_pipe[i][0], fd_in_out[1]);
		i++;
	}
	close_all_fd(fd_in_out, fd_pipe, argc - 4);
	wait_for_all_pids(id_cmd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_in_out[2];
	pid_t	id;

	if (argc != 5)
		ft_error("Error : incorrect number of arguments");
	fd_in_out[0] = open(argv[1], O_RDONLY);
	if (fd_in_out[0] == -1)
	{
		ft_error("Error : cannot open infile");
		exit(EXIT_FAILURE);
	}
	fd_in_out[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_in_out[1] == -1)
	{
		ft_error("Error : cannot create or write in outfile");
		exit(EXIT_FAILURE);
	}
	id = exec_cmds(fd_in_out, argc, argv, env);
	close_2_fd(fd_in_out[0], fd_in_out[1]);
	waitpid(id, NULL, 0);
}
