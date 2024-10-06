/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:58 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:26 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * The put_char_in_stdout() function writes a single character (c) to the standard output (file descriptor 1).
 * It increments the count of characters written in the data structure.
 */

void	put_char_in_stdout(t_data *data, int c)
{
	write(1, &c, 1);
	data->written++;
}

/*
 * The put_str_in_stdout() function outputs a string (str) to the standard output.
 * If the input string is NULL, it replaces it with the string "(null)".
 * It iterates through each character of the string and calls put_char_in_stdout() to output them one by one.
 */

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

/*
 * The render_char() function determines how to render a character or string based on the specifier in data->s.
 * If the specifier is '%', it outputs a '%' character.
 * If the specifier is 'c', it retrieves and outputs a character from the variadic arguments.
 * If the specifier is 's', it retrieves and outputs a string from the variadic arguments using put_str_in_stdout().
 */

void	render_char(t_data *data)
{
	if (*data->s == '%')
		put_char_in_stdout(data, '%');
	else if (*data->s == 'c')
		put_char_in_stdout(data, va_arg(data->ap, int));
	else if (*data->s == 's')
		put_str_in_stdout(data, va_arg(data->ap, char *));
}
