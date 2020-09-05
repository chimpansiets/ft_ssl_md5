/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotations_md5.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 13:51:19 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 13:56:19 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

long long	f1(long x, long y, long z)
{
	return ((x & y) | (~x & z));
}

long long	f2(long x, long y, long z)
{
	return ((x & z) | (y & ~z));
}

long long	f3(long x, long y, long z)
{
	return (x ^ y ^ z);
}

long long	f4(long x, long y, long z)
{
	return (y ^ (x | ~z));
}

long long	lrot(long x, long n)
{
	return ((x << n) | (x >> (32 - n)));
}
