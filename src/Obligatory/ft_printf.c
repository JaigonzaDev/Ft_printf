/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:45:02 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/04 16:37:20 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	render_format(t_data *data)
{
	if (my_strchr("cs%", *data->s))
		render_char(data);
	else
		render_num(data);
}

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

static t_bool	init_data(t_data *data, const char *str)
{
	data->written = 0;
	data->s = str;
	data->num_base = 0;
	return (TRUE);
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
