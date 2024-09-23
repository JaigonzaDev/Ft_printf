/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:32 by jaigonza          #+#    #+#             */
/*   Updated: 2024/07/03 18:28:12 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

//------------------------------------------------
// LIBS
//------------------------------------------------
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//------------------------------------------------
//
// MACROS
//
//------------------------------------------------
//------------------------------------------------
// Linux-Ubuntu x86_64 -> Virtual mem assign. getconfig PAGE_SIZE
//------------------------------------------------
# define BUFFER_SIZE 4096
# define UP_HEX "0123456789ABCDEF"
# define DOWN_HEX "0123456789abcdef"
//------------------------------------------------
//
// STRUCTS
//
//------------------------------------------------
//------------------------------------------------
// To have bool type data
//------------------------------------------------
typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef union u_promotion
{
	unsigned long	ul;
	long			l;
}					t_promotion;

//------------------------------------------------
// Flags
//------------------------------------------------
typedef struct s_flags
{
	t_bool			positive_flag;
	t_bool			minus_flag;
	t_bool			space_flag;
	t_bool			zero_flag;
	t_bool			hash_flag;
}					t_flags;
//------------------------------------------------
// Space [width] [precision]
//------------------------------------------------
typedef struct s_space
{
	int				width_value;
	int				precision_value;
	int				space_value;
	int				zeros_value;
}					t_space;

//------------------------------------------------
// Object data
//------------------------------------------------
typedef struct s_data
{
	// VA_LIST
	va_list			ap;
	// ORIGINAL STR
	const char		*s;
	int				written;
	char			specifier;

	// Num utils
	t_bool			uphex_flag;
	int				num_base;
	t_bool			negative_value;
	// Num tmp buff
	char			buf_tmp[64];
	int				buf_tmp_index;

	// BUFFER
	char			*buffer;
	int				buffer_index;

	// CONTROL
	t_flags			flags;
	t_space			space;
}					t_data;
//------------------------------------------------
//
// PROTOTYPES
//
//------------------------------------------------
// printf
//------------------------------------------------
int					ft_printf(char const *str, ...);
void				put_sign_in_buf(t_data *data);
void				stdout_buf(t_data *data);
void				write_in_buf(t_data *data, char c);
void				render_num(t_data *data);
void				render_format(t_data *data);
t_bool				check_format(t_data *data);
void				render_char(t_data *data);
t_bool				init_data(t_data *data, const char *str);
//------------------------------------------------
// format
//------------------------------------------------
void				check_flags(t_data *data);
void				check_value(t_data *data, int *value);
void				memset_structs(t_data *data);
void				check_num(t_data *data);
//------------------------------------------------
// render
//------------------------------------------------
void				render_str_in_buf(t_data *data, char *s);
void				render_char_in_buf(t_data *data, int c);
//------------------------------------------------
// render char
//------------------------------------------------
void				put_char_in_buf(char c, int precision, t_data *data);
void				put_str_in_buf(char *s, int precision, t_data *data);
void				set_space(t_data *data, char *s);
//------------------------------------------------
// utils
//------------------------------------------------
void				set_zeros(t_data *data);
void				set_spaces_num(t_data *data);
void				itoa_base_buf(t_data *data, t_promotion promo);
void				ft_memset(void *ptr, unsigned char c, size_t len);
t_bool				my_strchr(const char *s, char c);
void				memset_structs(t_data *data);
int					ft_strlen(const char *s);

#endif
