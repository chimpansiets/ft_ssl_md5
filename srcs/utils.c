/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/08 09:52:57 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/03 09:17:00 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	ft_get_len(uint32_t n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static char	*init(int *i)
{
	char *cmp;

	cmp = "0123456789abcdef";
	i[0] = 0;
	return (cmp);
}

static char	*free_str(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_strsub(str, 1, ft_strlen(str) - 1);
	free(tmp);
	return (str);
}

char		*ft_itoa_base_extra(uint32_t n, int base)
{
	int		i;
	int		len;
	char	*str;
	char	*cmp;

	cmp = init(&i);
	len = ft_get_len(n, base);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len + 1] = 0;
	while (len + 1)
	{
		str[len] = cmp[n % base];
		n = n / base;
		len--;
	}
	if (str[0] == '0')
		str = free_str(str);
	return (str);
}

char		*add00(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i < 8)
	{
		ft_printf("0");
		i++;
	}
	return (str);
}

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
