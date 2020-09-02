/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/08 09:52:57 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/02 12:25:52 by svoort        ########   odam.nl         */
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

void ft_printssl(t_ssl *ssl)
{
	ft_printf("len: %i\n", ssl->len);
	ft_printf("h0: %i\n", ssl->h0);
	ft_printf("h1: %i\n", ssl->h1);
	ft_printf("h2: %i\n", ssl->h2);
	ft_printf("h3: %i\n", ssl->h3);
	ft_printf("h4: %i\n", ssl->h4);
	ft_printf("h5: %i\n", ssl->h5);
	ft_printf("h6: %i\n", ssl->h6);
	ft_printf("h7: %i\n", ssl->h7);
	ft_printf("a: %i\n", ssl->a);
	ft_printf("b: %i\n", ssl->b);
	ft_printf("c: %i\n", ssl->c);
	ft_printf("d: %i\n", ssl->d);
	ft_printf("e: %i\n", ssl->e);
	ft_printf("f: %i\n", ssl->f);
	ft_printf("g: %i\n", ssl->g);
	ft_printf("h: %i\n", ssl->h);
	ft_printf("p: %i\n", ssl->p);
	ft_printf("q: %i\n", ssl->q);
	ft_printf("r: %i\n", ssl->r);
	ft_printf("s: %i\n", ssl->s);
	ft_printf("s0: %i\n", ssl->s0);
	ft_printf("s1: %i\n", ssl->s1);
	ft_printf("s2: %i\n", ssl->s2);
	ft_printf("s3: %i\n", ssl->s3);
	ft_printf("s4: %i\n", ssl->s4);
	ft_printf("s5: %i\n", ssl->s5);
	ft_printf("bytes: %s\n", ssl->bytes);
	ft_printf("bytes_32: %s\n", ssl->bytes_32);
	ft_printf("i: %i\n", ssl->i);
	ft_printf("tmp: %i\n", ssl->tmp);
	ft_printf("str: %i\n", ssl->str);
	ft_printf("stdin: %s\n", ssl->stdin);
	ft_printf("n_file: %i\n", ssl->n_file);
	ft_printf("pars: %i\n", ssl->pars);
	ft_printf("fd: %i\n", ssl->fd);
}

static int fd_is_valid(int fd)
{
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

char	*read_fd(int fd)
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
