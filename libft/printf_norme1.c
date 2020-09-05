/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_norme1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 14:01:31 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 14:09:02 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flsiz(char x)
{
	return (x == 'j' || x == 'z' || x == '#' || x == 'l' || x == 'h');
}

int		fl2(char x)
{
	return (x == ' ' || (x != 44 && x != 47 && x > 41 && x < 58) || x == 'L');
}

int		deval(char x)
{
	return (x == 'D' || x == 'd' || x == 'x' || x == 'O' || x == 'b');
}

int		deva2(char x)
{
	return (x == 'i' || x == 'o' || x == 'X' || x == 'u' || x == 'U');
}

int		oper(char x)
{
	return ((x < 96 || x > 103) && x != 105 && x != 120 && x != 114);
}
