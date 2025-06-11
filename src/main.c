/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:32 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:56:33 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	ft_parse(argc, argv, &var);
	init_var(&var);
	setup_window(&var);
	ft_free_all(&var);
	return (0);
}
