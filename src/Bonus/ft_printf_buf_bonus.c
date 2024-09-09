/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buf_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:37 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:21:52 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	write_in_buf(t_data *data, char c)
{
	if (data->buffer_index == BUFFER_SIZE)
	{
		stdout_buf(data);
	}
	data->buffer[data->buffer_index++] = c;
}

void	put_char_in_buf(char c, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision--)
		write_in_buf(data, c);
}

void	put_str_in_buf(char *s, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision-- && *s)
		write_in_buf(data, *s++);
}
