/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-sa <mruiz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:15:26 by mruiz-sa          #+#    #+#             */
/*   Updated: 2023/02/10 13:16:26 by mruiz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include<stdio.h>

int	ft_conversion(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		ft_print_c(va_arg(args, int), &len);
	else if (format == 's')
		ft_print_s(va_arg(args, char *), &len);
	else if (format == 'p')
	{
		ft_print_s("0x", &len);
		ft_print_x_p(va_arg(args, unsigned long int), format, &len);
	}
	else if (format == 'd' || format == 'i')
		ft_print_d_i(va_arg(args, int), &len);
	else if (format == 'u')
		ft_print_u(va_arg(args, unsigned int), &len);
	else if (format == 'x' || format == 'X')
		ft_print_x_p(va_arg(args, unsigned int), format, &len);
	else if (format == '%')
		ft_print_c('%', &len);
	return (len);
}

int	ft_printf(char const *str, ...)
{
	int		i;
	va_list	args;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] != 'c' && str[i + 1] != 's' && str[i + 1] != 'p'
				&& str[i + 1] != 'd' && str[i + 1] != 'i' && str[i + 1] != 'u'
				&& str[i + 1] != 'x' && str[i + 1] != 'X' && str[i + 1] != '%')
				return (ft_print_s("Wrong format\n", &len), -1);
			len = len + ft_conversion(args, str[i + 1]);
			i++;
		}
		else
			ft_print_c(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
