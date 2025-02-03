/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:49:56 by Lmatkows          #+#    #+#             */
/*   Updated: 2025/02/03 16:13:14 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	convertit un caractere majuscule en minuscule

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

/*
#include <stdio.h>

int main(void)
{
	printf("%c\n",ft_tolower('A'));
	printf("%c\n",ft_tolower('b'));
}
*/