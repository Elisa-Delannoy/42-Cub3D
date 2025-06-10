/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:23:06 by nrontard          #+#    #+#             */
/*   Updated: 2025/06/10 12:28:30 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>

// int main(void)
// {
// 	char str[19] = "test test test test";
// 	printf("%s\n", str);
// 	ft_bzero(str, sizeof(str));
// 	printf("%s\n", str);
// 	return(0);
// }