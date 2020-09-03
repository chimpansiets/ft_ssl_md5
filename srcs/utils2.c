/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/03 09:58:14 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/03 09:58:31 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	reverse_uint32(uint32_t n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

static int	fd_is_valid(int fd)
{
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

char		*read_fd(int fd)
{
	char	*text;
	char	*buf;
	int		ret;

	text = NULL;
	if (fd_is_valid(fd))
	{
		text = "";
		while (get_next_line(fd, &buf))
		{
			text = ft_joinfree(text, buf, 0);
			text = ft_joinfree(text, "\n", 0);
		}
	}
	return (text);
}
