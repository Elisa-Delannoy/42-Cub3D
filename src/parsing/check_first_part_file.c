#include "cub3D.h"

char	*check_texture(t_map *map, int i, int *j)
{
	int		start;
	char	*path;

	while (ft_check_space(map->tab_file[i][*j]) == 0)
		(*j)++;
	start = *j;
	while (map->tab_file[i][*j] && ft_check_space(map->tab_file[i][*j]) != 0
			&& map->tab_file[i][*j] != 10)
		(*j)++;
	path = ft_substr(map->tab_file[i], start, *j - start);
	while (map->tab_file[i][*j] && ft_check_space(map->tab_file[i][*j]) == 0)
		j++;
	if (map->tab_file[i][*j])
		return (free(path), NULL);
	return (path);
}

int	ft_one_instruct(t_map *map)
{
	if (map->c_no == 1 && map->c_so == 1 && map->c_we == 1 && map->c_ea == 1
		&& map->c_f == 1 && map->c_c == 1)
		return (0);
	else if (map->c_no > 1 || map->c_so > 1 || map->c_we > 1 || map->c_ea > 1
		|| map->c_f > 1 || map->c_c > 1)
		return (1);
	return (2);
}

int	check_btw_instruct_map(t_map *map, int *i)
{
	int	j;

	while (map->tab_file[*i])
	{
		j = 0;
		while (map->tab_file[*i][j])
		{
			if (ft_check_space(map->tab_file[*i][j]) == 0)
				j++;
			else if (map->tab_file[*i][j] == 10)
				break ;
			if (map->tab_file[*i][j] == '1')
				return (0);
			else if (map->tab_file[*i][j] && map->tab_file[*i][j] != ' '
					&& map->tab_file[*i][j] != 10)
				return (1);
		}
		*(i) += 1;
	}
	return (1);
}

int	check_coordinate_and_color(t_var *var, t_map *map, int i, int *j)
{
	while (map->tab_file[i][*j])
	{
		if (ft_is_coordinates(var, map, i, j) == 0
			|| ft_is_color(var, map, i, j) == 0)
			break ;
		else if (ft_check_space(map->tab_file[i][*j]) == 0)
			(*j)++;
		else if (map->tab_file[i][*j] == 10)
			break ;
		else
			return (ft_putstr_fd("Error : invalid instruction\n", 2), 1);
	}
	return (0);
}

int	ft_check_instruct(t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (var->map->tab_file[i])
	{
		j = 0;
		if (check_coordinate_and_color(var, var->map, i, &j) == 1)
			return (2);
		if (ft_one_instruct(var->map) == 1)
			return (ft_putstr_fd("Error : duplicate instructions\n", 2), 3);
		if (ft_one_instruct(var->map) == 0
			&& check_btw_instruct_map(var->map, &i) == 0)
		{
			if (check_map(var, &i) == 0)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (1);
}
