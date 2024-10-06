/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:41 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:30 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The check_num() function sets the number base for formatting based 
 * on the specifier character in the t_data structure. If the specifier 
 * is one of "diu", it sets the base to 10. If the specifier is 
 * "x", "X", or "p", it sets the base to 16. If the specifier is 'X', 
 * it also sets the uphex_flag to TRUE, indicating that uppercase 
 * hexadecimal letters should be used.
 */

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

/*
 * The ft_atoi() function converts a string representation of an 
 * integer to its corresponding integer value. It processes 
 * consecutive digit characters in the string and constructs 
 * the integer value by multiplying the current value by 10 
 * and adding the numeric value of the next digit. 
 * The function continues until a non-digit character is encountered.
 */

int	ft_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (my_strchr("0123456789", *data->s))
		value = (value * 10) + (*data->s++ - '0');
	return (value);
}

/*
 * The check_value() function checks if the current character in 
 * the t_data structure is a wildcard character ('*'). If it is, 
 * it retrieves the corresponding integer value from the 
 * variable arguments list using va_arg() and assigns it to 
 * the value pointer. If not, it calls ft_atoi() to convert 
 * the numeric string to an integer and assign it to the value pointer.
 */

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

/*
 * The check_flags() function processes format flags found in 
 * the t_data structure. It examines the characters in the format 
 * string and sets the appropriate flags in the data structure, 
 * such as zero_flag, positive_flag, space_flag, hash_flag, 
 * and minus_flag, depending on the characters encountered. 
 * The function continues to process characters until no more 
 * valid flags are found.
 */

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

/*
 * The check_format() function validates and processes the format 
 * specifier in the t_data structure. It initializes relevant 
 * structures and sets the precision value to -1. It calls 
 * check_flags() to handle any format flags and check_value() 
 * to retrieve the width value. If a '.' character is found, 
 * it processes the precision value. The function checks if 
 * the current character is a valid format specifier, and if so, 
 * it calls check_num() to determine the number base based on 
 * the specifier. It sets the specifier in the data structure 
 * and returns TRUE if everything is valid, or FALSE otherwise.
 */

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
