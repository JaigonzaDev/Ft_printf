/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_num_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:46 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 18:31:50 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

//[+ 0#-+][width][precision]
	// save in a tmp_buf the int -> char;
	//[width] [0]
	// write in buf
		// sign
		// zeros
		// number
		// spaces
		// spaces
		// sign
		// zeros
		// the number
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

	// contain integers
	// di -> signed int -> long
	// p -> unsigned long -> unsigned long
	// xXu -> unsigned int -> unsigned long
	//
	// stock in union
		//	data->format.signed_value = true;
	// render inside de buffer the int
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
