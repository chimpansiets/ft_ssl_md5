/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sha256_printing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 09:49:04 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/03 09:53:02 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "sha256.h"

void	print_strings_sha256(t_ssl *ssl, char **argv)
{
	ssl->i = 2;
	while (argv[ssl->i] && argv[ssl->i][0] == '-')
	{
		if (ft_strequ(argv[ssl->i], "-s") && argv[ssl->i + 1])
		{
			ssl->s = 1;
			if (ssl->r != 1 && ssl->q != 1)
				ft_printf("SHA256 (\"%s\") = ", argv[ssl->i + 1]);
			do_sha256(argv[(ssl->i) + 1], ssl);
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

void	print_files_sha256(t_ssl *ssl, int argc, char **av)
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
				ft_printf("SHA256 (%s) = ", av[ssl->i]);
			do_sha256(text, ssl);
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
