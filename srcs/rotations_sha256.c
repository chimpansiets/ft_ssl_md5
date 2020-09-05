/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotations_sha256.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 13:13:45 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 13:58:22 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

long long	rrot(long x, long n)
{
	return ((x >> n) | (x << (32 - n)));
}

long long	s1(long x)
{
	return (((rrot(x, 6)) ^ (rrot(x, 11)) ^ (rrot(x, 25))));
}

long long	ch(long x, long y, long z)
{
	return ((x & y) ^ (~x & z));
}

long long	s0(long x)
{
	return ((rrot(x, 2)) ^ (rrot(x, 13)) ^ (rrot(x, 22)));
}

long long	maj(long x, long y, long z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
