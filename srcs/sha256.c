/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sha256.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 09:22:59 by svoort        #+#    #+#                 */
/*   Updated: 2020/08/24 13:46:30 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

# define RROT(X, N) ((X >> N) | (X << (32 - N)))

# define S1(X) ((RROT(X, 6)) ^ (RROT(X, 11)) ^ (RROT(X, 25)))
# define CH(x, y, z) ((x & y) ^ (~ x & z))
# define S0(X) ((RROT(X, 2)) ^ (RROT(X, 13)) ^ (RROT(X, 22)))
# define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

static const uint32_t g_t[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void	init(t_ssl *ssl)
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

static int	padding_sha256(char *init_mg, int len, t_ssl *ssl)
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

static void	figure_out_hash(t_ssl *ssl, int i)
{
	int j;

	ssl->t = malloc(512);
	ft_bzero(ssl->t, 512);
	ft_memcpy(ssl->t, &ssl->bytes_32[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		ssl->s0 = RROT(ssl->t[j - 15], 7) ^
			RROT(ssl->t[j - 15], 18) ^ (ssl->t[j - 15] >> 3);
		ssl->s1 = RROT(ssl->t[j - 2], 17) ^
			RROT(ssl->t[j - 2], 19) ^ (ssl->t[j - 2] >> 10);
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

static void	swap_words(t_ssl *ssl, int j)
{
	ssl->s1 = S1(ssl->e);
	ssl->s2 = CH(ssl->e, ssl->f, ssl->g);
	ssl->s3 = ssl->h + ssl->s1 + ssl->s2 + g_t[j] + ssl->t[j];
	ssl->s0 = S0(ssl->a);
	ssl->s4 = MAJ(ssl->a, ssl->b, ssl->c);
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

int			sha256(char *init_mg, int len, t_ssl *ssl)
{
	int i;
	int j;

	init(ssl);
	padding_sha256(init_mg, len, ssl);
	i = 0;
	while (i < ssl->str)
	{
		figure_out_hash(ssl, i);
		j = -1;
		while (++j < 64)
			swap_words(ssl, j);
		ssl->h0 += ssl->a;
		ssl->h1 += ssl->b;
		ssl->h2 += ssl->c;
		ssl->h3 += ssl->d;
		ssl->h4 += ssl->e;
		ssl->h5 += ssl->f;
		ssl->h6 += ssl->g;
		ssl->h7 += ssl->h;
		free(ssl->t);
		i++;
	}
	free(ssl->bytes_32);
	return (0);
}

static void		do_again_sha256(t_ssl *g)
{
	char	*temp;

	temp = ft_itoa_base_extra(g->h3, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(g->h4, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(g->h5, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(g->h6, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(g->h7, 16);
	add00(temp);
	ft_putstr(temp);
	ft_putchar('\n');
	free(temp);
}

void			do_sha256(char *std, t_ssl *g)
{
	char	*temp;

	if (sha256(std, ft_strlen(std), g) == -1)
		return ;
	temp = ft_itoa_base_extra(g->h0, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(g->h1, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(g->h2, 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	do_again_sha256(g);
}

void    sha256_flag_flow(int argc, char **argv, t_ssl *ssl)
{
    if (ft_strequ(argv[ssl->i], "-s") && argv[ssl->i + 1])
    {
        ssl->s = 1;
		ft_printf("SHA256 (\"%s\") = ", argv[ssl->i + 1]);
        do_sha256(argv[(ssl->i) + 1], ssl);
        (ssl->i) += 2;
    }
    else if (ft_strequ(argv[ssl->i], "-r"))
    {
        ssl->r = 1;
        (ssl->i)++;
    }
    else if (ft_strequ(argv[ssl->i], "-q"))
    {
        ssl->q = 1;
        (ssl->i)++;
    }
}

void    sha256_loop(int argc, char **argv)
{
    t_ssl   ssl;
    int     fd;
    char    *text;

    ssl.i = 2;
	while (argv[ssl.i] && ft_strcmp(argv[ssl.i], "-p"))
	{
        ssl.p = 1;
		ssl.i++;
	}
	ssl.i = 2;
    while (argv[ssl.i] && argv[ssl.i][0] == '-')
        sha256_flag_flow(argc, argv, &ssl);
	ssl.stdin = read_fd(0);
	if (ssl.stdin)
	{
		if (ssl.p)
			ft_printf("%s\n", ssl.stdin);
		do_sha256(ssl.stdin, &ssl);
	}
    while (ssl.i < argc)
    {
        fd = open(argv[ssl.i], O_RDONLY);
        if (fd != -1)
        {
            text = read_fd(fd);
			ft_printf("SHA256 (\"%s\") = ", argv[ssl.i]);
            do_sha256(text, &ssl);
        }
        else
            ft_printf("%s: %s: No such file or directory\n", argv[1], argv[ssl.i]);
        ssl.i++;
    }
}
