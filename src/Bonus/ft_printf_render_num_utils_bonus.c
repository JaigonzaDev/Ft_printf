/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_num_utils_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:48 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:58:14 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	set_zeros_no_precision(t_data *data)
{
	if (data->flags.zero_flag && data->space.precision_value == -1)
	{
		if (data->flags.minus_flag)
			return ;
		if (data->space.width_value > data->buf_tmp_index)
			data->space.zeros_value = data->space.width_value
				- data->buf_tmp_index;
		if (data->specifier == 'u')
			return ;
		else if ((ft_strchr("xX", data->specifier) && data->flags.hash_flag
				&& data->buf_tmp[0] != '0') || (data->specifier != 'p'))
			data->space.zeros_value -= 2;
		else if ((data->negative_value || (!data->negative_value
					&& data->flags.positive_flag) || data->flags.space_flag))
			data->space.zeros_value--;
	}
}

void	set_zeros(t_data *data)
{
	if (data->space.precision_value >= 0)
	{
		if (data->space.precision_value >= data->buf_tmp_index)
		{
			data->space.zeros_value = data->space.precision_value
				- data->buf_tmp_index;
			return ;
		}
	}
	set_zeros_no_precision(data);
	if (data->space.zeros_value < 0)
		data->space.zeros_value = 0;
}

void	set_spaces_num(t_data *data)
{
	data->space.space_value = data->space.width_value - data->space.zeros_value
		- data->buf_tmp_index;
	if ((ft_strchr("xX", data->specifier) && data->flags.hash_flag == TRUE
			&& data->buf_tmp[0] != '0') || (data->specifier == 'p'))
	{
		data->space.space_value -= 2;
		return ;
	}
	if ((data->negative_value || (!data->negative_value
				&& data->flags.positive_flag) || (data->flags.space_flag
				&& data->negative_value)))
	{
		data->space.space_value--;
		return ;
	}
}

void	put_0x_in_buf(t_data *data)
{
	if (((ft_strchr("xX", *data->s)) && (data->flags.hash_flag)
			&& (data->buf_tmp[0] != '0')) || data->specifier == 'p')
	{
		if (data->specifier == 'X')
			put_str_in_buf("0X", 2, data);
		else
			put_str_in_buf("0x", 2, data);
	}
}

// 0x - +
void	put_sign_in_buf(t_data *data)
{
	if (data->num_base == 16)
		put_0x_in_buf(data);
	if (data->negative_value)
		put_char_in_buf('-', 1, data);
	else if (!data->negative_value)
	{
		if (data->flags.positive_flag)
			put_char_in_buf('+', 1, data);
		else if (!data->flags.positive_flag && data->flags.space_flag)
			put_char_in_buf(' ', 1, data);
	}
}
