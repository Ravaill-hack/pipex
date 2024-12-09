/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:22:13 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/11/05 16:27:16 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	These  functions  check  whether c falls into a certain character class
//	according  to the  specified  locale.   The functions without the "_l
//	suffix perform the check based on the current locale.

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
	int	c1;
	int	c2;

	c1 = 49;
	c2 = 67;
	printf("%d\n", ft_isdigit(c1));
	printf("%d\n", ft_isdigit(c2));
}
*/
