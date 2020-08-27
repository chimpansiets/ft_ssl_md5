/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ssl.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svoort <svoort@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 09:38:22 by svoort        #+#    #+#                 */
/*   Updated: 2020/08/24 13:42:39 by svoort        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/ft_printf.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef struct  s_flags {
    char        echo_stdin;
    char        quiet;
    char        reverse;
}               t_flags;

typedef struct		s_ssl
{
	int				len;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;
	uint32_t		h4;
	uint32_t		h5;
	uint32_t		h6;
	uint32_t		h7;
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
	uint32_t		p;
	uint32_t		q;
	uint32_t		r;
	uint32_t		s;
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		s2;
	uint32_t		s3;
	uint32_t		s4;
	uint32_t		s5;
	uint32_t		*t;
	char			*bytes;
	uint32_t		*bytes_32;
	int				i;
	uint32_t		tmp;
	int				str;
	char			*stdin;
	int				n_file;
	int				pars;
	int				fd;
}					t_ssl;

/*
**  parse_flags.c
*/

void            init_flags(t_flags *flags);
void            parse_flags(t_flags *flags, int argc, char **argv);

/*
**  md5.c
*/

char			*read_fd(int fd);
void            md5_loop(int argc, char **argv);
int				md5(unsigned char *init_mg, int len, t_ssl *ssl);
static void		figure_out_hash(t_ssl *ssl, int i);
static int		padding_md5(unsigned char *init_mg, int len, t_ssl *ssl);

/*
**	utils.c
*/

char			*add00(char *str);
char			*ft_itoa_base_extra(uint32_t n, int base);
uint32_t		reverse_uint32(uint32_t n);
void 			ft_printssl(t_ssl *ssl);

/*
**	sha256.c
*/

void    		sha256_loop(int argc, char **argv);

#endif
