/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 18:27:11 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/29 11:33:44 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n < 0)
		ft_putchar('-');
	if (n >= -9 && n <= 9)
	{
		if (n < 0)
			n = -n;
		ft_putchar(n + '0');
	}
	if (n < -9)
	{
		ft_putnbr(n / -10);
		ft_putnbr(-(n % 10));
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	ft_putnbrl(long n)
{
	if (n < 0)
		ft_putchar('-');
	if (n >= -9 && n <= 9)
	{
		if (n < 0)
			n = -n;
		ft_putchar(n + '0');
	}
	if (n < -9)
	{
		ft_putnbrl(n / -10);
		ft_putnbrl(-(n % 10));
	}
	if (n > 9)
	{
		ft_putnbrl(n / 10);
		ft_putnbrl(n % 10);
	}
}

void	ft_putnbrlu(unsigned long n)
{
	if (n <= 9)
		ft_putchar(n + '0');
	if (n > 9)
	{
		ft_putnbrlu(n / 10);
		ft_putnbrlu(n % 10);
	}
}

void	ft_putnbrll(long long n)
{
	if (n < 0)
		ft_putchar('-');
	if (n >= -9 && n <= 9)
	{
		if (n < 0)
			n = -n;
		ft_putchar(n + '0');
	}
	if (n < -9)
	{
		ft_putnbrll(n / -10);
		ft_putnbrll(-(n % 10));
	}
	if (n > 9)
	{
		ft_putnbrll(n / 10);
		ft_putnbrll(n % 10);
	}
}

void	ft_putnbrllu(unsigned long long n)
{
	if (n <= 9)
		ft_putchar(n + '0');
	if (n > 9)
	{
		ft_putnbrllu(n / 10);
		ft_putnbrllu(n % 10);
	}
}
