/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_norme2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 14:09:14 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 14:20:18 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ope2(char x)
{
	return (x != 115 && (x < 110 || x > 112) && x != 117 && x != 83);
}

int		ope3(char x)
{
	return ((x < 65 || x > 71) && x != 85 && x != 88 && x != 79);
}

int		invs(char j)
{
	return (j < 48 || j > 122 || (j > 57 && j < 65) || (j > 90 && j < 97));
}

int		inv1(char j, int base)
{
	return ((j > 64 && j < 91 && (j > base + 55 || base < 11)));
}

int		inv2(char j, int base)
{
	return ((j > 96 && j < 123 && (base < 11 || j > base + 87)));
}
