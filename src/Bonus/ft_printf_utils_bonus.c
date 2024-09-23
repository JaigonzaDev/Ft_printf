/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:51 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:46:59 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	memset_structs(t_data *data)
{
	ft_memset(&(data->flags), 0, sizeof(t_flags));
	ft_memset(&(data->space), 0, sizeof(t_space));
}

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

void	stdout_buf(t_data *data)
{
	if (data->buffer_index > 0)
	{
		data->written += write(1, data->buffer, data->buffer_index);
		ft_memset(data->buffer, 0, BUFFER_SIZE);
		data->buffer_index = 0;
	}
}
