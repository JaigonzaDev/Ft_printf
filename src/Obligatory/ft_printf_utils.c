/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:45:00 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 17:22:25 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	ft_strchr(const char *s, char c)
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
