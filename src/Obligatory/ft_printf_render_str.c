/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:58 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:48:25 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_char_in_stdout(t_data *data, int c)
{
	write(1, &c, 1);
	data->written++;
}

void	put_str_in_stdout(t_data *data, char *str)
{
	if (str == NULL)
	{
		str = "(null)";
	}
	while (*str)
	{
		put_char_in_stdout(data, (int)*str);
		str++;
	}
}

		// type promotion
void	render_char(t_data *data)
{
	if (*data->s == '%')
		put_char_in_stdout(data, '%');
	else if (*data->s == 'c')
		put_char_in_stdout(data, va_arg(data->ap, int));
	else if (*data->s == 's')
		put_str_in_stdout(data, va_arg(data->ap, char *));
}
