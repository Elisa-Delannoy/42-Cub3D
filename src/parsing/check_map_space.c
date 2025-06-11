/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:14 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:56:15 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_space_end(t_map *map)
{
	int		i;
	int		j;
	char	*space;
	char	*temp;

	i = 0;
	space = NULL;
	while (map->tab_map[i])
	{
		if ((int)ft_strlen(map->tab_map[i]) < map->width)
		{
			j = 0;
			while (map->tab_map[i][j])
				j++;
			space = malloc((map->width - j + 1) * sizeof (char));
			ft_memset(space, ' ', map->width - j);
			space[map->width - j] = '\0';
			temp = map->tab_map[i];
			map->tab_map[i] = ft_strjoin(temp, space);
			free(temp);
			free(space);
		}
		i++;
	}
}

int	check_ok_delete(char *tab)
{
	int	i;

	i = 1;
	if (tab == NULL)
		return (ft_putstr_fd("Error: invalid map (missing wall)", 2), 1);
	while (tab[i])
	{
		if (tab[i] == 'N' || tab[i] == 'S' || tab[i] == 'E'
			|| tab[i] == 'W' || tab[i] == '0' || tab[i] == 'D' || tab[i] == 'X')
			return (ft_putstr_fd("Error: invalid map (missing wall)\n", 2), 1);
		else if (tab[i] == ' ')
			i++;
		else
		{
			if (tab[i] == 'N' || tab[i] == 'S' || tab[i] == 'E'
				|| tab[i] == 'W' || tab[i] == '0' || tab[i] == 'D'
				|| tab[i] == 'X')
				return (ft_putstr_fd("Error: invalid map\n", 2), 1);
			else
				return (ft_putstr_fd("Error: invalid character\n", 2), 1);
		}
	}
	return (0);
}

int	delete_space(t_map *map)
{
	char	*line;
	char	*temp;
	int		i;
	int		len;

	i = 0;
	while (map->tab_map[i])
	{
		line = ft_strrchr(map->tab_map[i], '1');
		if (check_ok_delete(line) == 1)
			return (1);
		if (ft_strlen(line) > 1 && map->tab_map[i] != NULL)
		{
			temp = ft_strdup(map->tab_map[i]);
			len = (int)ft_strlen(temp) - (int)ft_strlen(line) + 1;
			free (map->tab_map[i]);
			map->tab_map[i] = ft_substr(temp, 0, len);
			free (temp);
		}
		if ((int)ft_strlen(map->tab_map[i]) > map->width)
			map->width = ft_strlen(map->tab_map[i]);
		i++;
	}
	map->height = i;
	return (0);
}

void	floodfill_space_wall(t_map *map, int x, int y, int c)
{
	if ((x < 0 || x >= map->height) || (y < 0 || y >= map->width))
		return ;
	if ((c == '1' && map->temp[x][y] != '1')
		|| (c == ' ' && map->temp[x][y] == ' '))
		map->temp[x][y] = '1';
	else
		return ;
	floodfill_space_wall(map, x + 1, y, c);
	floodfill_space_wall(map, x - 1, y, c);
	floodfill_space_wall(map, x, y + 1, c);
	floodfill_space_wall(map, x, y - 1, c);
}

void	check_space_in_map(t_var *var, int i, int j)
{
	var->map->temp = tab_cpy(var->map->tab_map, var->map->height);
	while (var->map->temp[i])
	{
		j = 0;
		if (i == 0 || i == var->map->height - 1)
		{
			while (var->map->temp[i][j])
			{
				if (var->map->temp[i][j] && var->map->temp[i][j] == ' ')
					floodfill_space_wall(var->map, i, j, ' ');
				else
					j++;
			}
		}
		else if (j == 0 && var->map->temp[i][j] == ' ')
			floodfill_space_wall(var->map, i, j, ' ');
		i++;
	}
	while (i > 0 && var->map->temp[--i])
	{
		if (ft_strrchr(var->map->temp[i], ' ') != NULL)
			return (ft_putstr_fd("Error: invalid character\n", 2),
				ft_free_all(var), exit(1));
	}
	free_split(var->map->temp);
}
