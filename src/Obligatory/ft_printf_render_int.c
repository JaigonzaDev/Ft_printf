/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_int.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:54 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 18:27:34 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_sing_in_stdout(t_data *data, t_promotion *promo)
{
	if (promo->l < 0)
	{
		promo->l = -(promo->l);
		put_char_in_stdout(data, '-');
	}
	if (data->specifier == 'p')
	{
		put_str_in_stdout(data, "0x");
		data->prefix_flag = TRUE;
	}
}

static void	itoa_base_stdout(t_data *data, t_promotion promo)
{
	t_promotion	tmp;

	if (!data->prefix_flag || promo.l < 0)
	{
		put_sing_in_stdout(data, &promo);
	}
	if (promo.ul < data->num_base)
	{
		if (data->specifier == 'X')
			put_char_in_stdout(data, UP_HEX[promo.ul]);
		else
		{
			put_char_in_stdout(data, DOWN_HEX[promo.ul]);
		}
	}
	else
	{
		tmp.ul = promo.ul / data->num_base;
		itoa_base_stdout(data, tmp);
		tmp.ul = promo.ul % data->num_base;
		itoa_base_stdout(data, tmp);
	}
}

	// contain integers
	// di -> signed int -> long
	// p -> unsigned long -> unsigned long
	// xXu -> unsigned int -> unsigned long
	//
	// stock in union
	// render inside de buffer the int
void	render_num(t_data *data)
{
	t_promotion	promo;

	promo.l = 0;
	if (ft_strchr("di", *data->s))
	{
		promo.l = (long)va_arg(data->ap, int);
	}
	else if (ft_strchr("p", *data->s))
	{
		promo.ul = (unsigned long)va_arg(data->ap, void *);
		if (promo.ul == 0)
		{
			put_str_in_stdout(data, "(nil)");
			return ;
		}
	}
	else if (ft_strchr("xXu", *data->s))
		promo.ul = (unsigned long)va_arg(data->ap, unsigned int);
	itoa_base_stdout(data, promo);
}
