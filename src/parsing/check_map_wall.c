/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:16 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/29 15:58:25 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_character(t_map *map)
{
	int		count_empty;

	count_empty = count_character(map->tab_map, '0');
	if (count_empty != count_character(map->temp, '0'))
		return (ft_putstr_fd("Error: invalid map (missing wall)\n", 2), 1);
	if (map->nb_door != count_character(map->temp, 'D'))
		return (ft_putstr_fd("Error: invalid map\n", 2), 1);
	if (0 == count_character(map->temp, 'N')
		&& 0 == count_character(map->temp, 'S')
		&& 0 == count_character(map->temp, 'E')
		&& 0 == count_character(map->temp, 'W'))
		return (ft_putstr_fd("Error: player should be in map\n", 2), 1);
	if (map->c_x && 1 != count_character(map->temp, 'X'))
		return (ft_putstr_fd("Error: invalid map\n", 2), 1);
	return (0);
}

int	check_wall(t_map *map)
{
	int	i;
	int	j;

	map->temp = tab_cpy(map->tab_map, map->height);
	i = 0;
	while (map->temp[i])
	{
		j = 0;
		while (map->temp[i][j])
		{
			if ((i == 0 || i == map->height - 1)
				&& !(map->temp[i][j] == '1' || map->temp[i][j] == ' '))
				return (ft_putstr_fd("Error: invalid map\n", 2), 1);
			if ((j == 0 || j == map->width - 1)
				&& !(map->temp[i][j] == '1' || map->temp[i][j] == ' '))
				return (ft_putstr_fd("Error: invalid map\n", 2), 1);
			if (ft_check_space(map->temp[i][j]) == 0)
				floodfill_space_wall(map, i, j, '1');
			j++;
		}
		i++;
	}
	if (check_character(map) == 1)
		return (1);
	return (0);
}

int	check_horizontal(char *tab, char c, char d)
{
	int	j;

	j = 0;
	while (tab[j] && (tab[j] == c || tab[j] == d))
		j++;
	if (tab[j])
		return (1);
	return (0);
}

int	check_vertical(t_map *map, int j, char c)
{
	int	i;

	i = 1;
	while (i < map->height)
	{
		j = 0;
		if (c == ' ')
		{
			while (map->tab_map[i][j] == ' ')
				j++;
		}
		if (map->tab_map[i][j] != '1'
			|| map->tab_map[i][ft_strlen(map->tab_map[i]) - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_outside_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->tab_map[i])
	{
		j = 0;
		while (map->tab_map[i][j])
		{
			if (map->tab_map[i][j] != '1')
				j++;
			else if ((i > 0 && map->tab_map[i - 1][j] != ' ')
				|| (i < map->height - 1 && map->tab_map[i + 1][j] != ' ')
				|| (j > 0 && map->tab_map[i][j - 1] != ' ')
				|| (j < map->width - 1 && map->tab_map[i][j + 1] != ' '))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
