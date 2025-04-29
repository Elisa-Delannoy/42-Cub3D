#include "../cub3D.h"

int	ft_check_space(t_map *map, int i, int j)
{
	if (map->map[i][j] == ' ')
		return (0);
	return (1);
}

int	ft_is_coordinates(t_map *map,int i, int *j)
{
	int	check;

	check = 0;
	if (map->map[i][*j + 2] == ' ')
	{
		if (map->map[i][*j] == 'N' && map->map[i][*j + 1] == 'O')
			map->no++;
		else if (map->map[i][*j] == 'S' && map->map[i][*j + 1] == 'O')
			map->so++;
		else if (map->map[i][*j] == 'W' && map->map[i][*j + 1] == 'E')
			map->we++;
		else if (map->map[i][*j] == 'E' && map->map[i][*j + 1] == 'A')
			map->ea++;
		else
			check = 1;
		if (check == 0)
		{
			*(j)+=2;
			return (0);
		}
	}
	return (1);
}

int	ft_is_color(t_map *map, int i, int *j)
{
	int	check;

	check = 0;
	if (map->map[i][*j + 1] == ' ')
	{
		if (map->map[i][*j] == 'F')
			map->f++;
		else if (map->map[i][*j] == 'C')
			map->c++;
		else
			check = 1;
		if (check == 0)
		{
			*(j)+=1;
			return (0);
		}
	}
	return (1);
}

int	ft_one_instruct(t_map *map)
{
	if (map->no == 1 && map->so == 1 && map->we == 1 && map->ea == 1
		&& map->f == 1 && map->c == 1)
		return (0);
	else if (map->no > 1 || map->so > 1 || map->we > 1 || map->ea > 1 || map->f > 1
			|| map->c > 1)
		return (1);
	return (2);
}

int	check_between_instruct_map(t_map *map, int *i)
{
	int	j;

	while(map->map[*i])
	{
		j = 0;
		while(map->map[*i][j])
		{
			if (ft_check_space(map, *i, j) == 0 || map->map[*i][j] == 10)
				j++;
			if (map->map[*i][j] == '1')
				return (0);
			else if (map->map[*i][j] && map->map[*i][j] != 32)
				return (1);
		}
		*(i)+=1;
	}
	return (1);
}

int	ft_check_instruct(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while(map->map[i][j])
		{
			// if (ft_is_coordinates(map, i, &j) == 0 || ft_is_color(map, i, &j) == 0 || ft_check_space (map, i, j) == 0 || map->map[i][j] == 10)
			// 	j++;
			if (ft_is_coordinates(map, i, &j) == 0 || ft_is_color(map, i, &j) == 0)
			{
				i++;
				j = 0; /*le temps de verifier ./chemin*/
			}
			else if (ft_check_space (map, i, j) == 0 || map->map[i][j] == 10)
				j++;
			else
				return (ft_putstr_fd("Error : invalid instruction\n", 2), 2); 
			if (ft_one_instruct(map) == 1)
				return (ft_putstr_fd("Error : duplicate instructions\n", 2), 3); 
			// else
			// 	return (1);
		}
		i++;
		if (ft_one_instruct(map) == 0 && check_between_instruct_map(map, &i ) == 0)
			return (0);
	}
	return (1);
}
/*GDB
display map->map[i]
display map->map[i][j]
display i
display j
*/

