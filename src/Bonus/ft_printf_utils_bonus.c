/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:51 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:27 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * The memset_structs() function initializes the flags and space 
 * structures within the t_data structure to zero. This ensures 
 * that any previous values do not interfere with subsequent 
 * formatting operations by resetting all flags and space 
 * parameters to a known initial state.
 */

void	memset_structs(t_data *data)
{
	ft_memset(&(data->flags), 0, sizeof(t_flags));
	ft_memset(&(data->space), 0, sizeof(t_space));
}

/*
 * The my_strchr() function searches for the first occurrence of 
 * the character 'c' in the string 's'. It returns TRUE if the 
 * character is found and FALSE if the string is NULL or the 
 * character is not found. This function is a safer alternative 
 * to the standard strchr() by providing a NULL check.
 */

t_bool	my_strchr(const char *s, char c)
{
	if (NULL == s)
		return (FALSE);
	while (*s)
	{
		if (*s == c)
			return (TRUE);
		++s;
	}
	return (FALSE);
}

/*
 * The ft_strlen() function calculates the length of the given 
 * string 's' by iterating through it until the null terminator 
 * is reached. It returns the total number of characters in the 
 * string, excluding the null terminator.
 */

int	ft_strlen(const char *s)
{
	const char	*p;
	size_t		i;

	p = s;
	i = 0;
	while (*p != '\0')
	{
		i++;
		p++;
	}
	return (i);
}

/*
 * The ft_memset() function fills a block of memory pointed to by 
 * 'ptr' with the specified byte 'c' for 'len' bytes. This is 
 * commonly used to initialize or reset memory regions to a 
 * specific value, such as zeroing out structures or buffers.
 */

void	ft_memset(void *ptr, unsigned char c, size_t len)
{
	unsigned char	*ptr_byte;

	ptr_byte = (unsigned char *)ptr;
	while (len)
	{
		*ptr_byte++ = c;
		--len;
	}
}

/*
 * The stdout_buf() function writes the contents of the buffer to 
 * standard output if there are any characters to write (i.e., if 
 * buffer_index is greater than 0). It updates the 'written' 
 * count to reflect how many bytes were written, clears the 
 * buffer by setting its contents to zero, and resets the 
 * buffer_index to 0, preparing it for the next output operation.
 */

void	stdout_buf(t_data *data)
{
	if (data->buffer_index > 0)
	{
		data->written += write(1, data->buffer, data->buffer_index);
		ft_memset(data->buffer, 0, BUFFER_SIZE);
		data->buffer_index = 0;
	}
}
