/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:09 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/09 11:24:38 by Lmatkows         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (argc != 5)
		return (1);
	int 	fd_in;
	int		fd_temp;
	int 	fd_out;
	char	*cmd1[2];
	char	*cmd2[2];

	fd_in = open(argv[1], O_RDONLY);
	fd_temp = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744);
	fd_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd_in < 0 || fd_out < 0 || fd_temp < 0)
		return (1);
	dup2(fd_in,	STDIN_FILENO);
	dup2(fd_temp, STDOUT_FILENO);
	execve(argv[2], {argv[2], NULL}, NULL);
	dup2(fd_temp,	STDIN_FILENO);
	dup2(fd_out,	STDOUT_FILENO);
	execve(argv[3], {argv[3], NULL}, NULL);
}
