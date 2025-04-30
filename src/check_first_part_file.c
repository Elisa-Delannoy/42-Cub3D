#include "../cub3D.h"

int	ft_check_space(t_map *map, int i, int j)
{
	if (map->tab_map[i][j] == ' ')
		return (0);
	return (1);
}

void	check_texture(t_map *map, int i, int *j)
{
	int	start;
	
	while (ft_check_space(map, i, *j) == 0)
		(*j)++;
	start = *j;
	while (ft_check_space(map, i, *j) != 0 && map->tab_map[i][*j] != 10)
		(*j)++;
	map->no = ft_substr(map->tab_map[i], start, *j - start);
	if (ft_check_space(map, i, *j) != 0 && map->tab_map[i][*j] != 10)
		return (ft_putstr_fd("Error path", 2), ft_free_all(map), exit(1));	
}

void	no(t_map *map, int i, int *j)
{
	int	fd;

	*j = *j + 2;
	map->c_no++;
	while (ft_check_space (map, i, *j) == 0)
		(*j)++;
	check_texture(map, i, j);
	// printf("%s$\n", map->no);
	fd = open("./path_to_the_north_texture.xpm", O_RDONLY); /*voir si mettre .xpm car map->no ne fonctionne pas*/
	if (fd == -1)
		return (ft_putstr_fd("Error read path", 2), ft_free_all(map), exit(1));
}


int	ft_is_coordinates(t_map *map,int i, int *j)
{
	if (map->tab_map[i][*j + 2] == ' ')
	{
		if (map->tab_map[i][*j] == 'N' && map->tab_map[i][*j + 1] == 'O')
			no(map, i, j);
		else if (map->tab_map[i][*j] == 'S' && map->tab_map[i][*j + 1] == 'O')
			map->c_so++; /*faire idem que pour no*/
		else if (map->tab_map[i][*j] == 'W' && map->tab_map[i][*j + 1] == 'E')
			map->c_we++;/*faire idem que pour no*/
		else if (map->tab_map[i][*j] == 'E' && map->tab_map[i][*j + 1] == 'A')
			map->c_ea++;/*faire idem que pour no*/
		else
			return (1);
		return (0);
	}
	return (2);
	
}

int	ft_is_color(t_map *map, int i, int *j)
{

	if (map->tab_map[i][*j + 1] == ' ')
	{
		if (map->tab_map[i][*j] == 'F')
			map->c_f++; /*faire idem que pour no*/
		else if (map->tab_map[i][*j] == 'C')
			map->c_c++;/*faire idem que pour no*/
		else
			return (1);
		return (0);
	}
	return (2);
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

	while(map->tab_map[*i])
	{
		j = 0;
		while(map->tab_map[*i][j])
		{
			if (ft_check_space(map, *i, j) == 0)
				j++;
			else if(map->tab_map[*i][j] == 10)
			{
				i++;
				j = 0;
			}
			if (map->tab_map[*i][j] == '1')
				return (0);
			else if (map->tab_map[*i][j] && map->tab_map[*i][j] != 32)
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
	while (map->tab_map[i])
	{
		j = 0;
		while(map->tab_map[i][j])
		{
			if (ft_is_coordinates(map, i, &j) == 0 || ft_is_color(map, i, &j) == 0)
				break;
			else if (ft_check_space (map, i, j) == 0)
				j++;
			else if (map->tab_map[i][j] == 10)
				break;
			else
				return (ft_putstr_fd("Error : invalid instruction\n", 2), ft_free_all(map), exit(2), 2); 
		}
		if (ft_one_instruct(map) == 1)
			return (ft_putstr_fd("Error : duplicate instructions\n", 2), ft_free_all(map), exit(3), 3); 
		if (ft_one_instruct(map) == 0 && ft_check_between_instruct_map(map, &i) == 0)
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
display map->tab_map[i]
display map->tab_map[i][j]
display i
display j


display map->tab_map[*i]
display map->tab_map[*i][j]
display *i
display j
*/

