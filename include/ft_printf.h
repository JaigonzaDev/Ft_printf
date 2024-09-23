/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:45:05 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:48:56 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> //variadic
# include <stdio.h>
# include <stdlib.h> //malloc && free
# include <unistd.h> //write

# define UP_HEX "0123456789ABCDEF"
# define DOWN_HEX "0123456789abcdef"

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef union u_promotion
{
	unsigned long	ul;
	long			l;
}					t_promotion;

typedef struct s_data
{
	va_list			ap;
	char			specifier;
	const char		*s;
	unsigned long	written;
	unsigned long	num_base;
	t_bool			prefix_flag;
}					t_data;

int	ft_printf(char const *str, ...);
t_bool				my_strchr(const char *s, char c);
void				render_num(t_data *data);
void				render_char(t_data *data);
void				put_char_in_stdout(t_data *data, int c);
void				put_str_in_stdout(t_data *data, char *str);

#endif
