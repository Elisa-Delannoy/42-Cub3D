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
			map->c_no++;
		else if (map->map[i][*j] == 'S' && map->map[i][*j + 1] == 'O')
			map->c_so++;
		else if (map->map[i][*j] == 'W' && map->map[i][*j + 1] == 'E')
			map->c_we++;
		else if (map->map[i][*j] == 'E' && map->map[i][*j + 1] == 'A')
			map->c_ea++;
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
			map->c_f++;
		else if (map->map[i][*j] == 'C')
			map->c_c++;
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
	if (map->c_no == 1 && map->c_so == 1 && map->c_we == 1 && map->c_ea == 1
		&& map->c_f == 1 && map->c_c == 1)
		return (0);
	else if (map->c_no > 1 && map->c_so > 1 && map->c_we > 1 && map->c_ea > 1
		&& map->c_f > 1 && map->c_c > 1)
		return (1);
	return (2);
}

int	ft_check_between_instruct_map(t_map *map, int *i)
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
				return (ft_putstr_fd("Error : invalid instruction\n", 2), ft_free_all(map), exit(2), 2); 
			if (ft_one_instruct(map) == 1)
				return (ft_putstr_fd("Error : duplicate instructions\n", 2), ft_free_all(map), exit(3), 3); 
			// else
			// 	return (1);
		}
		i++;
		if (ft_one_instruct(map) == 0 && ft_check_between_instruct_map(map, &i ) == 0)
		{
			map->i_begin_map = i;
			ft_check_ascii(map, &i);
			return (printf("%d maps ok\n", i), 0); /*mettre fonticon check map*/
		}
	}
	return (1);
}
/*GDB
display map->map[i]
display map->map[i][j]
display i
display j


display map->map[*i]
display map->map[*i][j]
display *i
display j
*/

