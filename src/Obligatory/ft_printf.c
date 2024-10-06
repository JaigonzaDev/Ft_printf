/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:45:02 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:32 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * The render_format() function determines how to render data based on the format 
 * specifier in the string (s) of the t_data structure. 
 * If the specifier is 'c', 's', or '%', it calls the render_char() function. 
 * Otherwise, it calls the render_num() function to handle numerical formats.
 */

static void	render_format(t_data *data)
{
	if (my_strchr("cs%", *data->s))
		render_char(data);
	else
		render_num(data);
}

/*
 * The check_format() function verifies if the format specifier in the string (s) 
 * of the t_data structure is valid. If the specifier is among the valid set 
 * ('c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'), it updates the num_base and 
 * sets the specifier field accordingly. It returns TRUE for valid specifiers 
 * and FALSE otherwise.
 */

static t_bool	check_format(t_data *data)
{
	if (!my_strchr("cspdiuxX%", *data->s))
		return (FALSE);
	if (my_strchr("diu", *data->s))
		data->num_base = 10;
	if (my_strchr("xXp", *data->s))
		data->num_base = 16;
	data->specifier = *data->s;
	data->prefix_flag = 0;
	return (TRUE);
}

/*
 * The init_data() function initializes the t_data structure by setting the 
 * written character count to zero, the string pointer to the provided string, 
 * and the numerical base to zero. It always returns TRUE, indicating successful 
 * initialization.
 */

static t_bool	init_data(t_data *data, const char *str)
{
	data->written = 0;
	data->s = str;
	data->num_base = 0;
	return (TRUE);
}

/*
 * The ft_printf() function mimics the behavior of the standard printf function. 
 * It takes a format string and a variable number of arguments. It initializes 
 * the t_data structure, processes the format string, and calls appropriate 
 * rendering functions for each format specifier encountered. It returns the 
 * total number of characters written.
 */

int	ft_printf(char const *str, ...)
{
	t_data	data;

	va_start(data.ap, str);
	if (!init_data(&data, str))
		return (-1);
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (!check_format(&data))
				return (-1);
			render_format(&data);
		}
		else
			put_char_in_stdout(&data, *data.s);
		++data.s;
	}
	va_end(data.ap);
	return (data.written);
}
