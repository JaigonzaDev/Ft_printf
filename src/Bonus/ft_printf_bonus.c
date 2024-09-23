/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:24 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/04 16:36:31 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	render_format(t_data *data)
{
	if (my_strchr("cs%", *data->s))
		render_char(data);
	else
		render_num(data);
}

	// rellena de 0;
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

void	clean_function(t_data *data)
{
	va_end(data->ap);
	free(data->buffer);
	data->buffer = NULL;
}

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
