/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sha256.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 09:22:59 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/03 09:57:48 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

int					sha256(char *init_mg, int len, t_ssl *ssl)
{
	int	i;
	int	j;

	init_h_sha(ssl);
	padding_sha256(init_mg, len, ssl);
	i = 0;
	while (i < ssl->str)
	{
		figure_out_hash_sha(ssl, i);
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

static void			do_again_sha256(t_ssl *g)
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
	free(temp);
}

void				do_sha256(char *std, t_ssl *g)
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

void				sha256_flag_flow(int argc, char **argv, t_ssl *ssl)
{
	if (ft_strequ(argv[ssl->i], "-s") && argv[ssl->i + 1])
	{
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
	else if (ft_strequ(argv[ssl->i], "-p"))
	{
		ssl->p = 1;
		(ssl->i)++;
	}
	else
		(ssl->i)++;
}

void				sha256_loop(int argc, char **argv)
{
	t_ssl	ssl;

	ft_bzero(&ssl, sizeof(t_ssl));
	ssl.i = 2;
	while (argv[ssl.i] && argv[ssl.i][0] == '-')
		sha256_flag_flow(argc, argv, &ssl);
	ssl.stdin = read_fd(0);
	if (ft_strlen(ssl.stdin) > 0 && !(ssl.i < argc && ssl.p == 0))
	{
		if (ssl.p)
			ft_printf("%s", ssl.stdin);
		do_sha256(ssl.stdin, &ssl);
		ft_printf("\n");
	}
	print_strings_sha256(&ssl, argv);
	print_files_sha256(&ssl, argc, argv);
}
