/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_chars_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:43 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:29 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The set_space() function calculates the amount of space that needs 
 * to be added before or after a string based on the specified width 
 * and precision values in the t_data structure. It determines the 
 * length of the string and adjusts the space_value accordingly, 
 * taking into account whether the precision is greater or less 
 * than the string length. If width_value is not greater than zero, 
 * it calculates space_value as the difference between width_value 
 * and string length.
 */

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

/*
 * The render_str_in_buf() function writes a string to the buffer, 
 * taking into account the specified width, precision, and flags 
 * in the t_data structure. If the string is NULL, it substitutes 
 * it with "(null)". It calculates the amount of space to be added 
 * using set_space(). Depending on the minus_flag, it either 
 * writes the string followed by spaces or spaces followed by the 
 * string, ensuring that the precision is respected if set.
 */

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

/*
 * The render_char_in_buf() function writes a single character to 
 * the buffer, considering the specified width in the t_data 
 * structure. If the width is greater than 1, it checks the 
 * minus_flag to determine if the character should be placed at 
 * the start or end, filling the remaining width with spaces. 
 * If the width is not greater than 1, it simply writes the 
 * character to the buffer.
 */

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
