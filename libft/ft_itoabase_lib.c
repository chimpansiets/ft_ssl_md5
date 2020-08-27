/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoabase_lib.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 10:15:26 by svoort        #+#    #+#                 */
/*   Updated: 2020/08/06 10:15:35 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoabase_lib(long n, int base)
{
	char	*rep_str;
	char	*str;
	int		len;

	len = ft_numdigits(n, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	rep_str = "0123456789abcdef";
	str[len] = '\0';
	str[0] = (n < 0) ? '-' : ' ';
	while (n != 0)
	{
		str[--len] = rep_str[(n % base) * ((n < 0) ? -1 : 1)];
		n /= base;
	}
	return (str);
}