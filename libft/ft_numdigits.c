/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numdigits.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 10:17:18 by svoort        #+#    #+#                 */
/*   Updated: 2020/08/06 10:17:21 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numdigits(long n, int base)
{
	int		len;

	if (n == 0)
		return (1);
	len = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
