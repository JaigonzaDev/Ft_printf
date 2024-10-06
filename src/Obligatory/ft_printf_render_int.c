/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_render_int.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:54 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:33 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * The put_sing_in_stdout() function outputs a sign to the standard output based on the value of promo.
 * If promo->l is negative, it converts it to positive and outputs a '-' character.
 * If the specifier in data is 'p', it prepends the string "0x" to indicate a pointer.
 */

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

/*
 * The itoa_base_stdout() function recursively converts an unsigned long integer (promo.ul)
 * to its string representation in a specified base (data->num_base) and outputs it to standard output.
 * If a prefix is required, it calls put_sing_in_stdout() to handle the sign.
 * The function differentiates between uppercase and lowercase hexadecimal outputs based on the specifier in data.
 */

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

/*
 * The render_num() function retrieves a number from the variadic arguments based on the specifier 
 * present in data->s and prepares it for rendering. It handles different types of specifiers: 
 * 'd' and 'i' for integers, 'p' for pointers, and 'x', 'X', and 'u' for unsigned integers.
 * It calls itoa_base_stdout() to convert the retrieved number to a string and output it.
 * If the pointer value is zero, it outputs "(nil)".
 */

void	render_num(t_data *data)
{
	t_promotion	promo;

	promo.l = 0;
	if (my_strchr("di", *data->s))
	{
		promo.l = (long)va_arg(data->ap, int);
	}
	else if (my_strchr("p", *data->s))
	{
		promo.ul = (unsigned long)va_arg(data->ap, void *);
		if (promo.ul == 0)
		{
			put_str_in_stdout(data, "(nil)");
			return ;
		}
	}
	else if (my_strchr("xXu", *data->s))
		promo.ul = (unsigned long)va_arg(data->ap, unsigned int);
	itoa_base_stdout(data, promo);
}
