/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_norme3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/05 14:23:24 by svoort        #+#    #+#                 */
/*   Updated: 2020/09/05 14:25:09 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		inv3(char j, int base)
{
	return ((j > 47 && j < 58 && j > base + 48));
}
