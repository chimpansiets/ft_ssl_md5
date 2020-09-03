/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   md5.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 10:51:49 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/03 09:48:00 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

void			init_h_md5(t_ssl *ssl)
{
	ssl->h0 = 0x67452301;
	ssl->h1 = 0xefcdab89;
	ssl->h2 = 0x98badcfe;
	ssl->h3 = 0x10325476;
}

int				md5(unsigned char *init_mg, int len, t_ssl *ssl)
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
			figure_out_hash_md5(ssl, i);
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
	free(temp);
}

void			md5_flag_flow(int argc, char **argv, t_ssl *ssl)
{
	if (ft_strequ(argv[ssl->i], "-s") && argv[ssl->i + 1])
		(ssl->i) += 2;
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
	else if (ft_strequ(argv[ssl->i], "-p"))
	{
		ssl->p = 1;
		(ssl->i)++;
	}
	else
		(ssl->i)++;
}

void			md5_loop(int argc, char **argv)
{
	t_ssl	ssl;

	ft_bzero(&ssl, sizeof(t_ssl));
	ssl.i = 2;
	while (argv[ssl.i] && argv[ssl.i][0] == '-')
		md5_flag_flow(argc, argv, &ssl);
	ssl.stdin = read_fd(0);
	if (ft_strlen(ssl.stdin) > 0 && !(ssl.i < argc && ssl.p == 0))
	{
		if (ssl.p)
			ft_printf("%s", ssl.stdin);
		do_md5(ssl.stdin, &ssl);
		ft_printf("\n");
	}
	print_strings_md5(&ssl, argv);
	print_files_md5(&ssl, argc, argv);
}
