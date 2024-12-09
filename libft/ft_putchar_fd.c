/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:57:28 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/11/05 16:28:11 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

//	Ecrit le caractere c sur la sortie file descriptor indiquee

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
