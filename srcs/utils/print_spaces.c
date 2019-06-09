/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galiza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:56:29 by galiza            #+#    #+#             */
/*   Updated: 2019/06/09 21:37:32 by pcorlys-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_accur(t_flags flags, int accur)
{
	int	tmp;
	int	size;
	int	len;

	size = 10;
	len = 0;
	tmp = (int)flags.flt;
	flags.flt -= (float)tmp;
	flags.flt = ABS(flags.flt);
	if (accur)
	{
		ft_putchar('.');
		len++;
	}
	return (len);
}

void	print_width(int width, t_flags flags)
{
	while (width-- > 0)
		flags.zero ? ft_putchar('0') : ft_putchar(' ');
}

int		ft_print_spaces(t_flags flags, int size_int)
{
	int	width;

	flags.t_dot -= size_int - (flags.total < 0 || flags.plus);
	if (flags.t_dot < 0)
		flags.t_dot = 0;
	width = ABS(flags.padding) - size_int - flags.t_dot;
	if (width < 0)
		width = 0;
	print_width(width, flags);
	return (width + flags.t_dot - ((!flags.total && !flags.un_tot)
	&& flags.t_dot > 0));
}

void	ft_get_int(const char *fmt, int curr_chr, t_flags *flags)
{
	int	i;

	i = (*flags).len;
	while ((fmt[curr_chr + i] < '1' || fmt[curr_chr + i] > '9') && i > 0)
		i--;
	while (((fmt[curr_chr + i] >= '0' && fmt[curr_chr + i] <= '9')
			|| fmt[curr_chr + i] == '.') && fmt[curr_chr + i])
		i--;
	i++;
	(*flags).l_int = i;
}

int		ft_print_keys(t_flags flags, int size_int)
{
	int	i;

	i = 0;
	if ((flags.total < 0 && ABS(flags.total) > 0) || 1 / flags.flt < 0)
	{
		ft_putchar('-');
		i = 1;
	}
	else if (flags.plus && flags.total >= 0)
	{
		ft_putchar('+');
		i = 1;
	}
	else if (flags.blank && flags.total > 0 && !flags.dot)
	{
		ft_putchar(' ');
		i = 1;
	}
	flags.t_dot -= size_int - (flags.total < 0 || flags.plus) +
			(!flags.total && !flags.un_tot);
	while (flags.t_dot-- > 0)
		ft_putchar('0');
	if (i)
		return (1);
	return (0);
}
