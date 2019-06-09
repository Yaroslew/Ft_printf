/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galiza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:20:04 by galiza            #+#    #+#             */
/*   Updated: 2019/06/09 16:44:04 by pcorlys-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*create_line(char *ftitoa, int time, char *line)
{
	char	*res;

	res = malloc(sizeof(char) * (time * 9) + 1);
	if (line)
	    res = ft_strcat(res, line);
	res = ft_strcat(res, ftitoa);
	free(ftitoa);
	if (line)
	    free(line);
	return (res);
}

static int		check_long_str(char *line, int accur)
{
	int		q;

	q = ft_strlen(line) - 1;
	if (q > accur)
	{
		while (q > accur)
		{
			if (line[q] < '4')
				return (0);
			q--;
		}
	}
	return (1);
}

static int putstr_frac(char *line, int accur)
{
    int q = 0;
    char sym;

    while (line[q] && q < accur)
    {
        sym = line[q];
        write(1, &sym, 1);
        q++;
    }
	return (q);
}

static void rouding(char *line, int accur)
{
    int q;
    int flag;

    flag = 0;
    q = ft_strlen(line) - 1;
	while (q > 0)
	{
		if (line[q] == '9' || line[q] == 58)
		{
			line[q] = '0';
			line[q - 1]++;
			if (q == accur)
				flag = 1;
		}
		if (q == accur && !flag)
			break;


		q--;
	}
}

static int		print_fract(long double n, int len, int accur)
{
	char *line;
	int check;
	int copy;
	int time;

	check = 1;
	time = 1;
	line = NULL;
	while (check)
	{
		copy = n;
		n -= copy;
		n *= 1000000000;
		line = create_line(ft_itoa(n), time, line);
		check = check_long_str(line, accur);
		time++;
	}
    rouding(line, accur);

	len += putstr_frac(line, accur);
	return (len);
}

int		ft_print_f(const char *fmt, va_list ap, int curr_chr, int len)
{
	t_flags			flags;
	int				s;
	double			n;
	int				accur;

	ft_get_keys(fmt, curr_chr, &flags);
	if (flags.t_dot <= 0 && flags.t_dot != -1)
		accur = 6;
	else
	{
		if (flags.t_dot == -1)
			accur = 0;
		else
			accur = flags.t_dot;
		flags.t_dot = 0;
	}
	if (flags.flags & LL)
		n = va_arg(ap, double);
	else if (flags.flags & L)
		n = va_arg(ap, double);
	else
	n = va_arg(ap, double);
	s = size(n);
	flags.flt = n;
	if (n < 0 || flags.plus)
		s++;
	if (((fmt[curr_chr + flags.l_int] == '0' && ft_atoi(fmt + curr_chr
	+ flags.l_int) != 0) || (fmt[curr_chr + flags.l_int - 1] == '+' &&
	fmt[curr_chr + flags.l_int - 2] == '0')) && !flags.minus && !flags.dot &&
		flags.padding > 0)
		flags.zero = 1;
	if (flags.minus)
	{
		len += ft_print_keys(flags, s);
		if (flags.t_dot > 0 || (n != 0) || !flags.dot)
			len += ft_putnbr(ABS(n));
		len += ft_print_accur(flags, accur);
		len += ft_print_spaces(flags, s + accur + 1);
	}
	else if (flags.zero)
	{
		len += ft_print_keys(flags, s);
		len += ft_print_spaces(flags, s + accur + 1);
		if (flags.t_dot > 0 || (n != 0) || !flags.dot)
			len += ft_putnbr(ABS(n));
		len += ft_print_accur(flags, accur);
	}
	else
	{
		len += ft_print_spaces(flags, s + accur + 1);
		len += ft_print_keys(flags, s);
		if (flags.t_dot > 0 || (n != 0) || !flags.dot)
			len += ft_putnbr(ABS(n));
		len += ft_print_accur(flags, accur);
	}
	len += print_fract(n, len, accur);
	return (ft_printf_aux(fmt, ap, curr_chr + flags.len + 1, len + accur));
}


