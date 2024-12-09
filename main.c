/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/09 19:34:33 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Ce programme permet d'envoyer le resultat de la commande ans un fichier
/*
int	main(int argc, char **argv)
{
	if (argc != 4)
		return (1);
	int 	fd_in;
	int 	fd_out;
	char	*cmd[2];

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd_in < 0 || fd_out < 0)
		return (1);
	cmd[0] = argv[2];
	cmd[1] = NULL;
	dup2(fd_in,	STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	execve(cmd[0], cmd, NULL);
}*/

int	find_line(char *title, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == title[j])
			j++;
		if (title[j] == '\0' && env[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_env(char *title, char **env)
{
	int	i;
	int	j;

	i = find_line(title, env);
	j = 0;
	if (i == -1 || !env[i])
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

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

char *first_word(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*word;

	i = 0;
	j = 0;
	len = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + len] != ' ' && str[i + len] != '\0')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = str[i + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	*extract_path(char **env, char *cmd)
{
	int		i;
	char	**raw;
	char	*name_cmd;
	char	*path;

	i = 0;
	raw = ft_split(extract_env("PATH", env), ':');
	name_cmd = first_word(cmd);
	while (raw[i])
	{
		path = ft_strjoin3(raw[i], "/", name_cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free(raw);
			return (path);
		}
		if (path)
			free(path);
		i++;
	}
	if (raw)
		ft_free(raw);
	if (name_cmd)
		free(name_cmd);
	return (cmd);
}

void	process(char *lstcmd, char **env)
{
	char	*cmd;
	char	*path;
	int		ret;

	cmd = first_word(lstcmd);
	path = extract_path(cmd, env);
	ret = execve(path, cmd, env);
	if (ret == -1)
	{
		ft_error2(cmd);
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
		ft_error1();
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
