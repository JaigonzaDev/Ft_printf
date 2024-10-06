/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:45:00 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 14:15:32 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * The my_strchr() function searches for the first occurrence of the character (c) 
 * in the string (s). If the string is NULL, it returns FALSE. 
 * The function iterates through the string until it finds the character or reaches 
 * the end of the string, returning TRUE if the character is found and FALSE otherwise.
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
