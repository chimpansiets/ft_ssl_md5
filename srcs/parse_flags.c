/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_flags.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 10:06:17 by svoort        #+#    #+#                 */
/*   Updated: 2020/08/05 15:45:13 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void    init_flags(t_flags *flags)
{
    flags->echo_stdin = 0;
    flags->quiet = 0;
    flags->reverse = 0;
}
