/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_chars_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:43 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:33:05 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

	// check width
			// write precise n from s
		// width - strlen [     hello]
void	set_space(t_data *data, char *s)
{
	int	len;

	len = ft_strlen(s);
	if (data->space.width_value > 0)
	{
		if (data->space.precision_value >= 0)
		{
			if (data->space.precision_value > len)
			{
				data->space.space_value = data->space.width_value - len;
			}
			else if (data->space.precision_value < len)
			{
				data->space.space_value = data->space.width_value
					- data->space.precision_value;
			}
		}
	}
	else
		data->space.space_value = data->space.width_value - len;
}

//[-][width][precision]
	// set space -> justified & width
	// write with justified
		// put string
		// put spaces
		// put string
void	render_str_in_buf(t_data *data, char *s)
{
	if (s == NULL)
	{
		s = "(null)";
	}
	set_space(data, s);
	if (data->flags.minus_flag)
	{
		if (data->space.precision_value >= 0)
			put_str_in_buf(s, data->space.precision_value, data);
		else
			put_str_in_buf(s, ft_strlen(s), data);
		put_char_in_buf(' ', data->space.space_value, data);
	}
	else
	{
		put_char_in_buf(' ', data->space.space_value, data);
		if (data->space.precision_value >= 0)
			put_str_in_buf(s, data->space.precision_value, data);
		else
			put_str_in_buf(s, ft_strlen(s), data);
	}
}

//[-][width]
void	render_char_in_buf(t_data *data, int c)
{
	int	width;

	width = data->space.width_value;
	if (width > 1)
	{
		if (data->flags.minus_flag)
		{
			put_char_in_buf((char)c, 1, data);
			put_char_in_buf(' ', width - 1, data);
		}
		else
		{
			put_char_in_buf(' ', width - 1, data);
			put_char_in_buf((char)c, 1, data);
		}
	}
	else
		put_char_in_buf((char)c, 1, data);
}

		// type promotion
void	render_char(t_data *data)
{
	if (*data->s == '%')
		render_char_in_buf(data, '%');
	else if (*data->s == 'c')
		render_char_in_buf(data, va_arg(data->ap, int));
	else if (*data->s == 's')
	{
		render_str_in_buf(data, va_arg(data->ap, char *));
	}
}
