/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:20:34 by lmatkows          #+#    #+#             */
/*   Updated: 2024/12/10 11:26:03 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*ft_strjoin3(char *s1, char *s2, char *s3);
void	ft_free(char **str);
int		find_line(char *title, char **env);
char	*first_word(char *str);
char	*extract_env(char *title, char **env);
char	*extract_path(char *cmd, char **env);
int		ft_error(int id);

#endif