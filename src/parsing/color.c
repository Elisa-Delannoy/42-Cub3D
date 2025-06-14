/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:20 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 18:47:06 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_color(char **color)
{
	int		i;
	int		j;
	int		check;
	char	**test;

	i = 0;
	check = 0;
	while (color[i])
	{
		j = 0;
		test = ft_split(color[i], ' ');
		if (test[0])
			check = ft_atoi(test[0]);
		else
			return (free_split(test), 1);
		if (test[1])
			return (free_split(test), 1);
		if (check < 0 || check > 255 || i > 2)
			return (free_split(test), 1);
		i++;
		free_split(test);
	}
	if (i < 3)
		return (1);
	return (0);
}

void	color_f(t_var *var, t_map *map, int i, int *j)
{
	int		start;
	char	**tab_f;

	*j = *j + 1;
	start = *j;
	map->c_f++;
	while (map->tab_file[i][*j] && (ft_check_space(map->tab_file[i][*j]) == 0
		|| ft_isdigit(map->tab_file[i][*j]) || map->tab_file[i][*j] == ','))
		(*j)++;
	tab_f = ft_split(map->tab_file[i] + start, ',');
	if (map->tab_file[i][*j] || check_color(tab_f) == 1)
		return (ft_putstr_fd("Error: invalid F color\n", 2),
			free_split(tab_f), ft_free_all(var), exit(1));
	map->color_f = rgb_to_int(tab_f);
	free_split(tab_f);
}

void	color_c(t_var *var, t_map *map, int i, int *j)
{
	int		start;
	char	**tab_c;

	*j = *j + 1;
	start = *j;
	map->c_c++;
	while (map->tab_file[i][*j] && (ft_check_space(map->tab_file[i][*j]) == 0
		|| ft_isdigit(map->tab_file[i][*j]) || map->tab_file[i][*j] == ','))
		(*j)++;
	tab_c = ft_split(map->tab_file[i] + start, ',');
	if (map->tab_file[i][*j] || check_color(tab_c) == 1)
		return (ft_putstr_fd("Error: invalid C color\n", 2),
			free_split(tab_c), ft_free_all(var), exit(1));
	map->color_c = rgb_to_int(tab_c);
	free_split(tab_c);
}

int	ft_is_color(t_var *var, t_map *map, int i, int *j)
{
	if (map->tab_file[i][*j] && map->tab_file[i][*j + 1] == ' ')
	{
		if (map->tab_file[i][*j] == 'F')
			color_f(var, map, i, j);
		else if (map->tab_file[i][*j] == 'C')
			color_c(var, map, i, j);
		else
			return (1);
		return (0);
	}
	return (2);
}
