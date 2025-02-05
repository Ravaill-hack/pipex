/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/05 14:33:00 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_all_pids(pid_t *id_cmd)
{
	waitpid(id_cmd[0], NULL, 0);
	waitpid(id_cmd[1], NULL, 0);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;
	int		err;

	split_cmd = ft_split(cmd, ' ');
	path = extract_path(split_cmd[0], env);
	err = execve(path, split_cmd, env);
	if (err == -1)
	{
		perror("Error : processus cannot be executed ");
		ft_free(split_cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
}

int	exec_cmds(char *cmd, char **env)
{
	int		fd_pipe[2];
	pid_t	id_cmd;

	if (pipe(fd_pipe) == -1)
		return (ft_error("Error : pipe creation failed\n"));
	id_cmd = fork();
	if (id_cmd == -1)
		return (ft_error("Error : fork execution failed\n"));
	if (id_cmd == 0)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		exec_cmd(cmd, env);
	}
	else
	{
		waitpid(id_cmd, NULL, 0);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
	}
	return (0);
}

int	ft_open_fd_in(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
		ft_error ("Error : cannot open infile\n");
	return (fd_in);
}

int	ft_open_fd_out(char *file, int i)
{
	int	fd_out;

	if (i == 0)
		fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		ft_error("Error : cannot create or write in outfile\n");
	return (fd_out);
}

int	ft_here_doc(char *str)
{
	int		fd_out;
	char	*line;

	fd_out = ft_open_fd_out(str, 1);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			close (fd_out);
			return (-1);
		}
		if (ft_strncmp(line, str, ft_strlen(str)) == 0)
		{
			free (line);
			close (fd_out);
			return (0);
		}
		ft_putstr_fd(line, fd_out);
	}
}

int	ft_find_i(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		return (3);
	else
		return (2);
}

int	ft_find_fd_in(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		return (ft_open_fd_in(argv[2]));
	else
		return (ft_open_fd_in(argv[1]));
}

int	main(int argc, char **argv, char **env)
{
	int		fd_in_out[2];
	int		i;

	if (argc < 5
		|| (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc >= 6))
		return (ft_error("Error : incorrect number of arguments\n"));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		ft_here_doc(argv[2]);
		fd_in_out[1] = ft_open_fd_out(argv[argc - 1], 1);
	}
	else
		fd_in_out[1] = ft_open_fd_out(argv[argc - 1], 0);
	fd_in_out[0] = ft_find_fd_in(argv);
	if (fd_in_out[0] == -1 || fd_in_out[1] == -1)
		return (-1);
	if (dup2(fd_in_out[0], STDIN_FILENO) == -1)
		return (ft_error("Error : fd_in assignation failed\n"));
	i = ft_find_i(argv);
	while (i < argc - 2)
		exec_cmds(argv[i++], env);
	unlink(argv[2]);
	if (dup2(fd_in_out[1], STDOUT_FILENO) == -1)
		return (ft_error("Error : fd_out assignation failed\n"));
	exec_cmd(argv[argc - 2], env);
	close_2_fd(fd_in_out[0], fd_in_out[1]);
}
