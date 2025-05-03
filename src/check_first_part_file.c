#include "../cub3D.h"

char	*check_texture(t_map *map, int i, int *j)
{
	int		start;
	char	*path;
	
	while (ft_check_space(map, i, *j) == 0)
		(*j)++;
	start = *j;
	while (map->tab_file[i][*j] && ft_check_space(map, i, *j) != 0
			&& map->tab_file[i][*j] != 10)
		(*j)++;
	path = ft_substr(map->tab_file[i], start, *j - start);
	while (map->tab_file[i][*j] && ft_check_space(map, i, *j) == 0)
		j++;
	if (map->tab_file[i][*j])
		return (printf("test"), free(path), NULL);
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
			if (ft_check_space(map, *i, j) == 0)
				j++;
			else if(map->tab_file[*i][j] == 10)
				break;
			if (map->tab_file[*i][j] == '1')
				return (0);
			else if (map->tab_file[*i][j] && map->tab_file[*i][j] != ' '
					&& map->tab_file[*i][j] != 10)
				return (1);
		}
		*(i)+=1;
	}
	return (1);
}

int		check_coordinate_and_color(t_map *map, int i, int *j)
{
	while(map->tab_file[i][*j])
	{
		if (ft_is_coordinates(map, i, j) == 0 || ft_is_color(map, i, j) == 0)
			break;
		else if (ft_check_space(map, i, *j) == 0)
			(*j)++;
		else if (map->tab_file[i][*j] == 10)
			break;
		else
			return (ft_putstr_fd("Error : invalid instruction\n", 2),
				ft_free_all(map), exit(2)), 2;
	}
	return (0);

}

int	ft_check_instruct(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->tab_file[i])
	{
		j = 0;
		check_coordinate_and_color(map, i, &j);
		if (ft_one_instruct(map) == 1)
			return (ft_putstr_fd("Error : duplicate instructions\n", 2),
				ft_free_all(map), exit(3), 3); 
		if (ft_one_instruct(map) == 0 && check_btw_instruct_map(map, &i) == 0)
		{

			map->i_begin_map = i;
			ft_check_ascii(map, &i);
			return (printf("%d maps ok\n", i), 0); /*mettre fonticon check map*/
		}
		i++;
	}
	return (1);
}
/*GDB
display map->tab_file[i]
display map->tab_file[i][j]
display i
display j


display map->tab_file[*i]
display map->tab_file[*i][j]
display *i
display j
*/

