/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:18 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/26 09:14:43 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	end_map(t_map *map, int i)
{
	int	j;

	while (map->tab_file[i])
	{
		j = 0;
		while (map->tab_file[i][j])
		{
			if (map->tab_file[i][j] == ' ')
				j++;
			else
				return (ft_putstr_fd("Error: invalid map\n", 2), 1);
		}
		i++;
	}
	return (0);
}

int	stock_map_in_tab(t_map *map, int *i)
{
	int	k;

	k = 0;
	map->tab_map = malloc((ft_lstsize(map->lst_map) + 1 - *i) * sizeof(char *));
	if (!map->tab_map)
		return (1);
	while (map->tab_file[*i])
	{
		if (ft_strrchr(map->tab_file[*i], '1') == NULL)
		{
			map->tab_map[k] = NULL;
			return (end_map(map, *i));
		}
		if (map->tab_file[*i])
			map->tab_map[k] = ft_strdup(map->tab_file[*i]);
		k++;
		(*i)++;
	}
	map->tab_map[k] = NULL;
	return (0);
}

void	ft_check_ascii(t_var *var, t_map *map, int i, int j)
{
	while (map->tab_map[++i])
	{
		j = 0;
		while (map->tab_map[i][j])
		{
			if (check_w_s_d(map, i, j) == 1)
				j++;
			else if (map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S'
				|| map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W')
			{
				if (var->player != 0)
					return (ft_putstr_fd("Error: should have only one "
							"player\n", 2), ft_free_all(var), exit(2));
				var->player = init_player(var, i, j);
				j++;
			}
			else
				return (ft_putstr_fd("Error: invalid character\n", 2),
					ft_free_all(var), exit(2));
		}
	}
	if (var->player == NULL)
		return (ft_putstr_fd("Error: player is missing\n", 2),
			ft_free_all(var), exit(2));
}

int	count_character(char **tab, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_map(t_var *var, int *i)
{
	if (stock_map_in_tab(var->map, i) == 1)
		return (1);
	if (delete_space(var->map) == 1)
		return (1);
	ft_check_ascii(var, var->map, -1, 0);
	add_space_end(var->map);
	check_space_in_map(var, 0, 0);
	var->map->temp = NULL;
	if (check_wall(var->map) == 1)
		return (1);
	if (check_outside_wall(var->map) == 0)
		return (ft_putstr_fd("Error: invalid map\n", 2),
			ft_free_all(var), exit(2), 1);
	return (0);
}
