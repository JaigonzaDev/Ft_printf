/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:41 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:31:51 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	check_num(t_data *data)
{
	if (my_strchr("diu", *data->s))
		data->num_base = 10;
	else if (my_strchr("xXp", *data->s))
	{
		data->num_base = 16;
		if (*data->s == 'X')
			data->uphex_flag = TRUE;
	}
}

	// Convert char to int - store in value

int	ft_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (my_strchr("0123456789", *data->s))
		value = (value * 10) + (*data->s++ - '0');
	return (value);
}

void	check_value(t_data *data, int *value)
{
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		++data->s;
		return ;
	}
	*value = ft_atoi(data);
}

void	check_flags(t_data *data)
{
	char	flag;

	while (my_strchr("0 +#-", *data->s))
	{
		flag = *data->s;
		if (flag == '0')
			data->flags.zero_flag = TRUE;
		else if (flag == '+')
			data->flags.positive_flag = TRUE;
		else if (flag == ' ')
			data->flags.space_flag = TRUE;
		else if (flag == '#')
			data->flags.hash_flag = TRUE;
		else if (flag == '-')
			data->flags.minus_flag = TRUE;
		++data->s;
	}
}

	// init data
	// I can have precision = 0.
	// bool flags
	// width
	// precision
t_bool	check_format(t_data *data)
{
	memset_structs(data);
	data->space.precision_value = -1;
	check_flags(data);
	check_value(data, &(data->space.width_value));
	if (*data->s == '.' && *(++data->s))
		check_value(data, &(data->space.precision_value));
	if (!my_strchr("cspdiuxX%", *data->s))
		return (FALSE);
	else
	{
		if (my_strchr("diuxXp", *data->s))
			check_num(data);
		data->specifier = *data->s;
		return (TRUE);
	}
}
