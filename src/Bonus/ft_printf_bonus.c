/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:24 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:31 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The render_format() function determines how to render data based on the format 
 * specifier in the string (s) of the t_data structure. 
 * If the specifier is 'c', 's', or '%', it calls the render_char() function. 
 * Otherwise, it calls the render_num() function to handle numerical formats.
 */

void	render_format(t_data *data)
{
	if (my_strchr("cs%", *data->s))
		render_char(data);
	else
		render_num(data);
}

/*
 * The init_data() function initializes the t_data structure by setting the 
 * written character count to zero, the string pointer to the provided string, 
 * and allocating memory for a buffer of a specified size. If memory allocation 
 * fails, it returns FALSE. It also initializes the buffer to zero and sets 
 * the buffer index and temporary buffer index to zero. 
 * It returns TRUE upon successful initialization.
 */

t_bool	init_data(t_data *data, const char *str)
{
	data->written = 0;
	data->s = str;
	data->buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!data->buffer)
		return (FALSE);
	data->buffer_index = 0;
	ft_memset(data->buffer, 0, BUFFER_SIZE * sizeof(char));
	data->buf_tmp_index = 0;
	return (TRUE);
}

/*
 * The clean_function() function cleans up the resources associated with the 
 * t_data structure. It ends the variable argument list using va_end(), 
 * frees the allocated memory for the buffer, and sets the buffer pointer to 
 * NULL to prevent dangling pointers.
 */

void	clean_function(t_data *data)
{
	va_end(data->ap);
	free(data->buffer);
	data->buffer = NULL;
}

/*
 * The ft_printf() function mimics the behavior of the standard printf function. 
 * It takes a format string and a variable number of arguments. It initializes 
 * the t_data structure, processes the format string, and calls appropriate 
 * rendering functions for each format specifier encountered. If a valid 
 * specifier is found, it renders the corresponding output; otherwise, it writes 
 * regular characters to the buffer. Finally, it outputs the buffered data, 
 * cleans up resources, and returns the total number of characters written.
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
			{
				free(data.buffer);
				data.buffer = NULL;
				return (-1);
			}
			render_format(&data);
		}
		else
			write_in_buf(&data, *data.s);
		++data.s;
	}
	stdout_buf(&data);
	clean_function(&data);
	return (data.written);
}
