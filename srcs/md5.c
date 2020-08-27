/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   md5.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 10:51:49 by svoort        #+#    #+#                 */
/*   Updated: 2020/08/24 13:40:02 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

# define F1(x, y, z) ((x & y) | (~x & z))
# define F2(x, y, z) ((x & z) | (y & ~z))
# define F3(x, y, z) (x ^ y ^ z)
# define F4(x, y, z) (y ^ (x | ~z))

# define LROT(X, N) ((X << N) | (X >> (32 - N)))

static const uint32_t g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t g_t[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static void	init(t_ssl *ssl)
{
	ssl->h0 = 0x67452301;
	ssl->h1 = 0xefcdab89;
	ssl->h2 = 0x98badcfe;
	ssl->h3 = 0x10325476;
}

static int	padding_md5(unsigned char *init_mg, int len, t_ssl *ssl)
{
	init(ssl);
	ssl->len = len + 1;
	while (ssl->len % 64 != 56)
		ssl->len++;
	if (!(ssl->bytes = malloc(ssl->len + 64)))
		return (-1);
	ssl->bytes = ft_bzero(ssl->bytes, ssl->len + 64);
	ft_strcpy((char*)ssl->bytes, (const char *)init_mg);
	*(uint32_t*)(ssl->bytes + len) = 0x80;
	*(uint32_t*)(ssl->bytes + ssl->len) = (uint32_t)(8 * len);
	ssl->str = 0;
	return (0);
}

static void	figure_out_hash(t_ssl *ssl, int i)
{
	if (i < 16)
	{
		ssl->f = F1(ssl->b, ssl->c, ssl->d);
		ssl->g = i;
	}
	else if (i < 32)
	{
		ssl->f = F2(ssl->b, ssl->c, ssl->d);
		ssl->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		ssl->f = F3(ssl->b, ssl->c, ssl->d);
		ssl->g = (3 * i + 5) % 16;
	}
	else
	{
		ssl->f = F4(ssl->b, ssl->c, ssl->d);
		ssl->g = (7 * i) % 16;
	}
	ssl->tmp = ssl->d;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->b + LROT((ssl->a + ssl->f + g_t[i] + ssl->t[ssl->g]), g_s[i]);
	ssl->a = ssl->tmp;
}

int			md5(unsigned char *init_mg, int len, t_ssl *ssl)
{
	int i;

	if (padding_md5(init_mg, len, ssl) == -1)
		return (-1);
	while (ssl->str < ssl->len)
	{
		ssl->t = (uint32_t *)(ssl->bytes + ssl->str);
		ssl->a = ssl->h0;
		ssl->b = ssl->h1;
		ssl->c = ssl->h2;
		ssl->d = ssl->h3;
		i = -1;
		while (++i < 64)
			figure_out_hash(ssl, i);
		ssl->h0 += ssl->a;
		ssl->h1 += ssl->b;
		ssl->h2 += ssl->c;
		ssl->h3 += ssl->d;
		ssl->str += 64;
	}
	free(ssl->bytes);
	return (0);
}

void			do_md5(char *std, t_ssl *g)
{
	char	*temp;

	if (md5((uint8_t *)std, ft_strlen(std), g) == -1)
		return ;
	temp = ft_itoa_base_extra(reverse_uint32(g->h0), 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(reverse_uint32(g->h1), 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(reverse_uint32(g->h2), 16);
	add00(temp);
	ft_putstr(temp);
	free(temp);
	temp = ft_itoa_base_extra(reverse_uint32(g->h3), 16);
	add00(temp);
	ft_putstr(temp);
    ft_putchar('\n');
	free(temp);
}

char	*read_fd(int fd)
{
    char    *text;
    char    *buf;

	text = NULL;
	if (read(fd, &buf, 0))
	{
		while (get_next_line(fd, &buf))
		{
			text = ft_joinfree(text, buf, 1);
			text = ft_joinfree(text, "\n", 1);
		}
	}
    return (text);
}

void    md5_flag_flow(int argc, char **argv, t_ssl *ssl)
{
    if (ft_strequ(argv[ssl->i], "-s") && argv[ssl->i + 1])
    {
        ssl->s = 1;
		ft_printf("MD5 (\"%s\") = ", argv[ssl->i + 1]);
        do_md5(argv[(ssl->i) + 1], ssl);
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

void    md5_loop(int argc, char **argv)
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
        md5_flag_flow(argc, argv, &ssl);
	ssl.stdin = read_fd(0);
	if (ssl.stdin)
	{
		if (ssl.p)
			ft_printf("%s\n", ssl.stdin);
		do_md5(ssl.stdin, &ssl);
	}
    while (ssl.i < argc)
    {
        fd = open(argv[ssl.i], O_RDONLY);
        if (fd != -1)
        {
            text = read_fd(fd);
			ft_printf("MD5 (\"%s\") = ", argv[ssl.i]);
            do_md5(text, &ssl);
        }
        else
            ft_printf("%s: %s: No such file or directory\n", argv[1], argv[ssl.i]);
        ssl.i++;
    }
}
