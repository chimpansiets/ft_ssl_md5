/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoabase.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/25 13:14:41 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 14:24:57 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		validbase(char *s, int base, int l, int j)
{
	if (base < 2 || base > 36)
	{
		ft_printf("error: \"%d\" cannot be base", base);
		return (0);
	}
	while (*s)
	{
		if (*s > 64 && *s < 91)
			j = (int)*s;
		else if (*s > 96 && *s < 123)
			l = (int)*s;
		if (inv1(*s, base) || inv2(*s, base) || inv3(*s, base))
		{
			ft_printf("error: \'%c\' too large or small for %d base", *s, base);
			return (0);
		}
		if (l > 0 && j > 0)
		{
			ft_printf("error: \'%c\' && \'%c\' cannot be in one base", l, j);
			return (0);
		}
		s++;
	}
	return (1);
}

static	char	*transbase(uintmax_t nbr, int base, int reg)
{
	int			i;
	int			tmp;
	int			ost;
	char		buf[65];

	ft_ifupper(&reg, &tmp);
	if (base < 2 || base > 36)
		return (0);
	i = 64;
	buf[i] = '\0';
	if (nbr == 0)
		return (ft_strdup("0"));
	while (nbr)
	{
		ost = nbr % base;
		nbr = nbr / base;
		i--;
		if (ost > 9)
			buf[i] = ost + tmp;
		else
			buf[i] = ost + 48;
	}
	return (ft_strdup(buf + i));
}

static	char	*sigitoa(intmax_t c, char *res, int i)
{
	i = ft_nbrlen(c, 1);
	if (c < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	res = (char *)malloc(i + 1);
	if (!(res))
		return (0);
	res[i] = '\0';
	if (c < 0)
	{
		c = -c;
		res[0] = '-';
		while (i > 1)
		{
			i--;
			res[i] = c % 10 + 48;
			c /= 10;
		}
	}
	else
		convert_pos(&i, &res, &c);
	return (res);
}

uintmax_t		ft_basetoint(char *s, int base)
{
	uintmax_t	i;
	int			j;
	uintmax_t	l;

	if (!(validbase(s, base, 0, 0)))
		return (0);
	j = ft_strlen(s);
	i = 1;
	l = 0;
	while (j)
	{
		j--;
		check_char(&s, &l, j, i);
		i *= base;
		if (invs(s[j]))
		{
			ft_printf("error: \'%c\' doesn't belong to any base", s[j]);
			return (0);
		}
	}
	return (l);
}

/*
**	itoa_base that works with unsigned long long integers, and just
**	long long integers. How? you might ask. well, magic.
**	It takes a unsigned long long integer as argument.
**	However, if sys is equal to 1. It converts it to
**	just a long long integer and works with that.
*/

char			*ft_itoabase(uintmax_t c, int sys, int rg)
{
	int			i;
	char		*res;

	res = NULL;
	if (sys == 1)
		return (sigitoa(c, res, 0));
	else if (sys)
		return (transbase(c, sys, rg));
	i = ft_nbrlen(c, 0);
	res = (char *)malloc(i + 1);
	if (!(res))
		return (0);
	res[i] = '\0';
	while (i)
	{
		i--;
		res[i] = c % 10 + 48;
		c /= 10;
	}
	return (res);
}
