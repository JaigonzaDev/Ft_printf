/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_num_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:46 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:28 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The itoa_base_buf() function converts a numeric value to its 
 * string representation in a specified base, storing the result 
 * in the temporary buffer of the t_data structure. If the 
 * promotion value (promo.l) is negative, it sets the negative_value 
 * flag to TRUE and negates the value. If the promotion value (promo.ul) 
 * is less than the base, it directly stores the corresponding character 
 * from either the uppercase or lowercase hexadecimal arrays, depending 
 * on the uphex_flag. For larger values, it recursively divides the 
 * value by the base and stores the resulting characters in the buffer.
 */

void	itoa_base_buf(t_data *data, t_promotion promo)
{
	t_promotion	tmp;

	if (promo.l < 0)
	{
		data->negative_value = TRUE;
		promo.l = -(promo.l);
	}
	else if (promo.ul < (unsigned long)data->num_base)
	{
		if (data->uphex_flag)
			data->buf_tmp[data->buf_tmp_index++] = UP_HEX[promo.ul];
		else
		{
			data->buf_tmp[data->buf_tmp_index++] = DOWN_HEX[promo.ul];
		}
	}
	else
	{
		tmp.ul = promo.ul / data->num_base;
		itoa_base_buf(data, tmp);
		tmp.ul = promo.ul % data->num_base;
		itoa_base_buf(data, tmp);
	}
}

/*
 * The render_num_in_buf() function formats and outputs a number to 
 * the buffer based on the specifications in the t_data structure. 
 * It first converts the numeric value to a string representation 
 * using itoa_base_buf(), then adjusts the output based on the 
 * zero and space padding flags. If the minus_flag is set, it writes 
 * the sign (if applicable), followed by any leading zeros, and then 
 * the numeric string. If the minus_flag is not set, it writes any 
 * leading spaces before the sign and zeros, then the numeric string.
 */

void	render_num_in_buf(t_data *data, t_promotion promo)
{
	itoa_base_buf(data, promo);
	set_zeros(data);
	set_spaces_num(data);
	if (data->flags.minus_flag)
	{
		put_sign_in_buf(data);
		put_char_in_buf('0', data->space.zeros_value, data);
		put_str_in_buf(data->buf_tmp, data->buf_tmp_index, data);
		put_char_in_buf(' ', data->space.space_value, data);
	}
	else
	{
		put_char_in_buf(' ', data->space.space_value, data);
		put_sign_in_buf(data);
		put_char_in_buf('0', data->space.zeros_value, data);
		put_str_in_buf(data->buf_tmp, data->buf_tmp_index, data);
	}
}
/*
 * The render_num() function retrieves a numeric value from the 
 * variable arguments based on the format specifier in the t_data 
 * structure. It initializes a t_promotion structure to hold the 
 * retrieved value, which can be a signed integer, pointer address, 
 * or unsigned integer, depending on the specifier. If the format 
 * specifies a pointer and the value is NULL, it outputs "(nil)" 
 * to the buffer. Finally, it calls render_num_in_buf() to handle 
 * the formatted output of the number to the buffer.
 */

void	render_num(t_data *data)
{
	t_promotion	promo;

	promo.l = 0;
	if (my_strchr("di", *data->s))
		promo.l = (long)va_arg(data->ap, int);
	else if (my_strchr("p", *data->s))
	{
		promo.ul = (unsigned long)va_arg(data->ap, void *);
		if (promo.ul == 0)
		{
			put_str_in_buf("(nil)", 5, data);
			return ;
		}
	}
	else if (my_strchr("xXu", *data->s))
		promo.ul = (unsigned long)va_arg(data->ap, unsigned int);
	render_num_in_buf(data, promo);
}
