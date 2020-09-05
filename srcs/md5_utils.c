/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   md5_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 09:19:18 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 13:56:19 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

int			padding_md5(unsigned char *init_mg, int len, t_ssl *ssl)
{
	init_h_md5(ssl);
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

void		figure_out_hash_md5(t_ssl *ssl, int i)
{
	if (i < 16)
	{
		ssl->f = f1(ssl->b, ssl->c, ssl->d);
		ssl->g = i;
	}
	else if (i < 32)
	{
		ssl->f = f2(ssl->b, ssl->c, ssl->d);
		ssl->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		ssl->f = f3(ssl->b, ssl->c, ssl->d);
		ssl->g = (3 * i + 5) % 16;
	}
	else
	{
		ssl->f = f4(ssl->b, ssl->c, ssl->d);
		ssl->g = (7 * i) % 16;
	}
	ssl->tmp = ssl->d;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->b + lrot((ssl->a + ssl->f + g_t[i] + ssl->t[ssl->g]), g_s[i]);
	ssl->a = ssl->tmp;
}

void		print_strings_md5(t_ssl *ssl, char **argv)
{
	ssl->i = 2;
	while (argv[ssl->i] && argv[ssl->i][0] == '-')
	{
		if (ft_strequ(argv[ssl->i], "-s") && argv[ssl->i + 1])
		{
			ssl->s = 1;
			if (ssl->r != 1 && ssl->q != 1)
				ft_printf("MD5 (\"%s\") = ", argv[ssl->i + 1]);
			do_md5(argv[(ssl->i) + 1], ssl);
			if (ssl->r == 1 && ssl->q != 1)
				ft_printf(" \"%s\"\n", argv[ssl->i + 1]);
			else
				ft_printf("\n");
			ssl->i += 2;
		}
		else
			ssl->i++;
	}
}

void		print_files_md5(t_ssl *ssl, int argc, char **av)
{
	int		fd;
	char	*text;

	while (ssl->i < argc)
	{
		fd = open(av[ssl->i], O_RDONLY);
		if (fd != -1)
		{
			text = read_fd(fd);
			if (ssl->r != 1 && ssl->q != 1)
				ft_printf("MD5 (%s) = ", av[ssl->i]);
			do_md5(text, ssl);
			if (ssl->r == 1 && ssl->q != 1)
				ft_printf(" %s\n", av[ssl->i]);
			else
				ft_printf("\n");
		}
		else
			ft_printf("%s: %s: No such file or directory\n", av[1], av[ssl->i]);
		ssl->i++;
	}
}
