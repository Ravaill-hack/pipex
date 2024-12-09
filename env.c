/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:58:25 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/12/09 20:07:19 by Lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*extract_path(char *cmd, char **env)
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
