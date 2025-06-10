#include "cub3D.h"

int	check_wall(t_map *map)
{
	int		count;
	int		i;
	int		j;

	i = 0;
	map->temp = tab_cpy(map->tab_map, map->height);
	count = count_empty(map->tab_map);
	while (map->temp[i])
	{
		j = 0;
		while (map->temp[i][j])
		{
			if (ft_check_space(map->temp[i][j]) == 0)
				floodfill_space_wall(map, i, j, '1');
			j++;
		}
		i++;
	}
	if (count != count_empty(map->temp))
		return (ft_putstr_fd("Error: invalid map (missing wall)\n", 2), 1);
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

int	check_wall_min_max(t_var *var)
{
	if (check_horizontal(var->map->tab_map[0], '1', '1') == 0
		&& !check_horizontal(var->map->tab_map[var->map->height - 1], '1', '1')
		&& check_vertical(var->map, 0, '1') == 0)
		return (0);
	if (check_horizontal(var->map->tab_map[0], '1', ' ') != 0
		|| check_horizontal(var->map->tab_map[var->map->height - 1], '1', ' ')
		|| check_vertical(var->map, 0, ' ') != 0)
		return (ft_putstr_fd("Error : invalid map (missing wall)\n", 2),
			ft_free_all(var), exit(1), 1);
	return (2);
}
