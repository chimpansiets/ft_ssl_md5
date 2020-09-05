/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sha256_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 09:42:51 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 14:04:30 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

void	init_h_sha(t_ssl *ssl)
{
	ssl->h0 = 0x6a09e667;
	ssl->h1 = 0xbb67ae85;
	ssl->h2 = 0x3c6ef372;
	ssl->h3 = 0xa54ff53a;
	ssl->h4 = 0x510e527f;
	ssl->h5 = 0x9b05688c;
	ssl->h6 = 0x1f83d9ab;
	ssl->h7 = 0x5be0cd19;
}

int		padding_sha256(char *init_mg, int len, t_ssl *ssl)
{
	int i;

	ssl->len = len * 8;
	ssl->str = 1 + ((ssl->len + 16 + 64) / 512);
	if (!(ssl->bytes_32 = malloc(16 * ssl->str * 4)))
		return (-1);
	ft_bzero(ssl->bytes_32, 16 * ssl->str * 4);
	ft_memcpy((char *)ssl->bytes_32, init_mg, ft_strlen(init_mg));
	((char *)ssl->bytes_32)[ft_strlen(init_mg)] = 0x80;
	i = 0;
	while (i < (ssl->str * 16) - 1)
	{
		ssl->bytes_32[i] = reverse_uint32(ssl->bytes_32[i]);
		i++;
	}
	ssl->bytes_32[((ssl->str * 512 - 64) / 32) + 1] = ssl->len;
	return (0);
}

void	figure_out_hash_sha(t_ssl *ssl, int i)
{
	int j;

	ssl->t = malloc(512);
	ft_bzero(ssl->t, 512);
	ft_memcpy(ssl->t, &ssl->bytes_32[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		ssl->s0 = rrot(ssl->t[j - 15], 7) ^
			rrot(ssl->t[j - 15], 18) ^ (ssl->t[j - 15] >> 3);
		ssl->s1 = rrot(ssl->t[j - 2], 17) ^
			rrot(ssl->t[j - 2], 19) ^ (ssl->t[j - 2] >> 10);
		ssl->t[j] = ssl->t[j - 16] + ssl->s0 + ssl->t[j - 7] + ssl->s1;
		j++;
	}
	ssl->a = ssl->h0;
	ssl->b = ssl->h1;
	ssl->c = ssl->h2;
	ssl->d = ssl->h3;
	ssl->e = ssl->h4;
	ssl->f = ssl->h5;
	ssl->g = ssl->h6;
	ssl->h = ssl->h7;
}

void	swap_words(t_ssl *ssl, int j)
{
	ssl->s1 = s1(ssl->e);
	ssl->s2 = ch(ssl->e, ssl->f, ssl->g);
	ssl->s3 = ssl->h + ssl->s1 + ssl->s2 + g_t[j] + ssl->t[j];
	ssl->s0 = s0(ssl->a);
	ssl->s4 = maj(ssl->a, ssl->b, ssl->c);
	ssl->s5 = ssl->s0 + ssl->s4;
	ssl->h = ssl->g;
	ssl->g = ssl->f;
	ssl->f = ssl->e;
	ssl->e = ssl->d + ssl->s3;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->a;
	ssl->a = ssl->s3 + ssl->s5;
}
