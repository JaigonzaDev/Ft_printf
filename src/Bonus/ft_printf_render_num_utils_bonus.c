/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_num_utils_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:48 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:28 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The set_zeros_no_precision() function calculates the number of 
 * leading zeros to be added based on the flags and the width 
 * specified in the t_data structure when no precision is set. 
 * If the zero_flag is active and precision_value is -1, it 
 * determines the number of zeros based on the width and the 
 * content of the buffer. It also checks for special cases, 
 * such as when the specifier is 'u', 'x', 'X', or 'p', and 
 * adjusts the zeros_value accordingly.
 */

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
		else if ((my_strchr("xX", data->specifier) && data->flags.hash_flag
				&& data->buf_tmp[0] != '0') || (data->specifier != 'p'))
			data->space.zeros_value -= 2;
		else if ((data->negative_value || (!data->negative_value
					&& data->flags.positive_flag) || data->flags.space_flag))
			data->space.zeros_value--;
	}
}

/*
 * The set_zeros() function determines the number of leading zeros 
 * to add based on the precision specified in the t_data structure. 
 * If precision_value is greater than or equal to zero, it calculates 
 * the necessary zeros based on the difference between precision_value 
 * and the length of the current buffer. If precision_value is less 
 * than zero, it delegates to set_zeros_no_precision() to handle 
 * the case where no precision is set, ensuring zeros_value is non-negative.
 */

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

/*
 * The set_spaces_num() function calculates the number of leading 
 * spaces to add in front of the number based on the width, zeros, 
 * and the current length of the buffer. It adjusts the space_value 
 * based on whether the number is negative, if a positive sign 
 * should be displayed, or if a space should be added. For special 
 * cases such as hexadecimal numbers with hash_flag or pointers, 
 * it also deducts 2 from the space_value to account for the 
 * "0x" or "0X" prefix.
 */

void	set_spaces_num(t_data *data)
{
	data->space.space_value = data->space.width_value - data->space.zeros_value
		- data->buf_tmp_index;
	if ((my_strchr("xX", data->specifier) && data->flags.hash_flag == TRUE
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

/*
 * The put_0x_in_buf() function writes the "0x" or "0X" prefix to 
 * the buffer for hexadecimal numbers or pointers when the hash_flag 
 * is set. It checks the current specifier and writes the appropriate 
 * prefix to the buffer, ensuring that it does not prepend "0x" 
 * when the buffer's first character is '0'.
 */

void	put_0x_in_buf(t_data *data)
{
	if (((my_strchr("xX", *data->s)) && (data->flags.hash_flag)
			&& (data->buf_tmp[0] != '0')) || data->specifier == 'p')
	{
		if (data->specifier == 'X')
			put_str_in_buf("0X", 2, data);
		else
			put_str_in_buf("0x", 2, data);
	}
}

/*
 * The put_sign_in_buf() function handles writing the sign or prefix 
 * for numbers to the buffer based on the flags and the base. It first 
 * checks if the base is hexadecimal and calls put_0x_in_buf() to 
 * potentially write the prefix. If the value is negative, it writes 
 * a '-' sign. If the value is not negative, it checks the flags to 
 * determine whether to write a '+' sign or a space character.
 */

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
