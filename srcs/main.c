/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 09:33:42 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/03 09:13:12 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char **argv)
{
	t_flags flags;

	init_flags(&flags);
	if (argc < 2)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		if (argv[1] && ft_strequ(argv[1], "md5"))
			md5_loop(argc, argv);
		else if (argv[1] && ft_strequ(argv[1], "sha256"))
			sha256_loop(argc, argv);
	}
	return (0);
}
