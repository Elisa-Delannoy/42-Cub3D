/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:31:14 by nrontard          #+#    #+#             */
/*   Updated: 2025/02/25 15:49:20 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fdi(int n, int fd)
{
	long	nb;

	nb = n;
	if (n < 0)
	{
		ft_putchari('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fdi(nb / 10, fd);
		ft_putnbr_fdi(nb % 10, fd);
	}
	else
	{
		ft_putchari(nb + '0');
	}
	return (ft_len_nbr(n));
}

int	ft_putnbr_u(unsigned long n, int fd)
{
	unsigned long	nb;

	nb = n;
	if (nb > 9)
	{
		ft_putnbr_fdi(nb / 10, fd);
		ft_putnbr_fdi(nb % 10, fd);
	}
	else
	{
		ft_putchari(nb + '0');
	}
	return (ft_len_nbru(n));
}

int	ft_putstr_fdi(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fdi("(null)", 1));
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_puthexanbr_fd(size_t n, int fd, char c)
{
	size_t	nb;

	nb = n;
	if (nb >= 16)
	{
		ft_puthexanbr_fd(nb / 16, fd, c);
		ft_puthexanbr_fd(nb % 16, fd, c);
	}
	else if (c == 'x' || c == 'p')
		ft_putchari(BASE16[nb]);
	else if (c == 'X')
		ft_putchari(BASE16M[nb]);
	return (ft_len_hexa(n));
}
