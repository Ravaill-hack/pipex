/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/10 16:44:16 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_all_pids(pid_t *id_cmd)
{
	int	i;

	i = 0;
	while (id_cmd[i])
	{
		waitpid(id_cmd[i], NULL, 0);
		i++;
	}
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

pid_t	exec_2_cmd(int fd_in, int fd_out, char **cmd, char **env)
{
	int		fd_pipe[2];
	pid_t	id_cmd[2];

	if (pipe(fd_pipe) == -1)
		return (ft_error("Error : pipe creation failed"));
	id_cmd[0] = fork();
	if (id_cmd[0] == -1)
		return (ft_error("Error : fork execution failed"));
	if (id_cmd[0] == 0)
	{
		close(fd_pipe[0]);
		exec_cmd(cmd[0], env, fd_in, fd_pipe[1]);
	}
	id_cmd[1] = fork();
	if (id_cmd[1] == -1)
		return (ft_error("Error : fork execution failed"));
	if (id_cmd[1] == 0)
	{
		close(fd_pipe[1]);
		exec_cmd(cmd[1], env, fd_pipe[0], fd_out);
	}
	close_all_fd(fd_in, fd_out, fd_pipe);
	wait_for_all_pids(id_cmd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		fd_in;
	int		fd_out;
	pid_t	id;
	char	**cmd;

	cmd = NULL;
	if (argc != 5)
		ft_error("Error : incorrect number of arguments");
	cmd = organize_cmd(argc, argv);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		ft_error("Error : cannot open infile");
		exit(EXIT_FAILURE);
	}
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_error("Error : cannot create or write in outfile");
		exit(EXIT_FAILURE);
	}
	id = exec_2_cmd(fd_in, fd_out, cmd, env);
	close_2_fd(fd_in, fd_out);
	waitpid(id, NULL, 0);
}
