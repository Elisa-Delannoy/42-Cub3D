#include "cub3D.h"

int	check_color(char **color)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (color[i])
	{
		check = ft_atoi(color[i]);
		if (check < 0 || check > 255 || i > 2)
			return (1);
		i++;
	}
	return (0);
}

void	color_f(t_var *var, t_map *map, int i, int *j)
{
	int		start;

	*j = *j + 1;
	start = *j;
	map->c_f++;
	while (map->tab_file[i][*j] && (ft_check_space(map->tab_file[i][*j]) == 0
		|| ft_isdigit(map->tab_file[i][*j]) || map->tab_file[i][*j] == ','))
		(*j)++;
	map->f = ft_split(map->tab_file[i] + start, ',');
	if (map->tab_file[i][*j] || check_color(map->f) == 1)
		return (ft_putstr_fd("Error : invalid F color\n", 2), ft_free_all(var),
			exit(1));
}

void	color_c(t_var *var, t_map *map, int i, int *j)
{
	int		start;

	*j = *j + 1;
	start = *j;
	map->c_c++;
	while (map->tab_file[i][*j] && (ft_check_space(map->tab_file[i][*j]) == 0
		|| ft_isdigit(map->tab_file[i][*j]) || map->tab_file[i][*j] == ','))
		(*j)++;
	map->c = ft_split(map->tab_file[i] + start, ',');
	if (map->tab_file[i][*j] || check_color(map->c) == 1)
		return (ft_putstr_fd("Error : invalid C color\n", 2), ft_free_all(var),
			exit(1));
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
