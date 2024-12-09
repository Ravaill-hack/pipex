/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatkows <lmatkows@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:33:30 by Lmatkows          #+#    #+#             */
/*   Updated: 2024/11/05 16:27:15 by lmatkows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	These  functions  check  whether c falls into a certain character class
//	according  to the  specified  locale.   The functions without the "_l
//	suffix perform the check based on the current locale.

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
	int	c1;
	int	c2;

	c1 = 67;
	c2 = 128;
	printf("%d\n", ft_isascii(c1));
	printf("%d\n", ft_isascii(c2));
}
*/
