#include "cub3D.h"

char	*check_texture(t_map *map, int i, int *j)
{
	int		start;
	char	*path;

	start = *j;
	while (map->tab_file[i][*j] && ft_check_space(map->tab_file[i][*j]) != 0
			&& map->tab_file[i][*j] != 10)
		(*j)++;
	path = ft_substr(map->tab_file[i], start, *j - start);
	while (map->tab_file[i][*j] && ft_check_space(map->tab_file[i][*j]) == 0)
		(*j)++;
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
		|| map->c_f > 1 || map->c_c > 1 || map->c_d > 1) /*bonus*/
		return (1);
	return (2);
}

int	check_btw_instruct_map(t_var *var, int *i)
{
	int	j;

	while (var->map->tab_file[*i])
	{
		j = 0;
		while (var->map->tab_file[*i][j])
		{
			if (ft_is_door(var, var->map, *i, &j) == 0) /*bonnus*/
				break ; /*bonnus*/
			if (ft_check_space(var->map->tab_file[*i][j]) == 0)
				j++;
			else if (var->map->tab_file[*i][j] == 10)
				break ;
			if (var->map->tab_file[*i][j] == '1')
				return (0);
			else if (var->map->tab_file[*i][j] && var->map->tab_file[*i][j] != ' '
					&& var->map->tab_file[*i][j] != 10)
				return (ft_putstr_fd("Error : invalid map\n", 2), 1);
		}
		*(i) += 1;
	}
	ft_putstr_fd("Error : no map\n", 2);
	return (1);
}

int	check_coordinate_and_color(t_var *var, t_map *map, int i, int *j)
{
	while (map->tab_file[i][*j])
	{
		if (ft_is_coordinates(var, map, i, j) == 0
			|| ft_is_color(var, map, i, j) == 0
			|| ft_is_door(var, map, i, j) == 0) /*bonnus*/
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
	while (i < ft_lstsize(var->map->lst_map) && var->map->tab_file[i])
	{
		j = 0;
		if (ft_one_instruct(var->map) == 0)
		{
			if (check_btw_instruct_map(var, &i) == 0
				&& check_map(var, &i) == 0)
				return (0);
			else
				return (1);
		}
		else if (ft_one_instruct(var->map) == 2 
			&& check_coordinate_and_color(var, var->map, i, &j) == 1)
			return (2);
		else if (ft_one_instruct(var->map) == 1)
			return (ft_putstr_fd("Error : duplicate instructions\n", 2), 3);
		i++;
	}
	return (1);
}
