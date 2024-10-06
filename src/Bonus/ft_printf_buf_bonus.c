/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buf_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:37 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:31 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The write_in_buf() function writes a character to the buffer in the 
 * t_data structure. If the buffer is full (i.e., if the buffer index 
 * equals BUFFER_SIZE), it calls stdout_buf() to output the current 
 * contents of the buffer before adding the new character. 
 * The character is then stored in the buffer at the current index, 
 * and the index is incremented to point to the next available position.
 */

void	write_in_buf(t_data *data, char c)
{
	if (data->buffer_index == BUFFER_SIZE)
	{
		stdout_buf(data);
	}
	data->buffer[data->buffer_index++] = c;
}

/*
 * The put_char_in_buf() function writes a specified character to the 
 * buffer multiple times, determined by the given precision. 
 * If the precision is less than or equal to zero, the function returns 
 * without writing anything. Otherwise, it calls write_in_buf() in a 
 * loop to write the character to the buffer for the specified number 
 * of times.
 */

void	put_char_in_buf(char c, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision--)
		write_in_buf(data, c);
}

/*
 * The put_str_in_buf() function writes a string to the buffer in the 
 * t_data structure, up to a specified precision limit. If the precision 
 * is less than or equal to zero, the function returns without writing 
 * anything. The function iterates through the string and writes each 
 * character to the buffer until the precision limit is reached or the 
 * end of the string is encountered.
 */

void	put_str_in_buf(char *s, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision-- && *s)
		write_in_buf(data, *s++);
}
