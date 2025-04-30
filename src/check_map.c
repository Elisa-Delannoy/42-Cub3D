#include "../cub3D.h"

void	ft_check_ascii(t_map *map, int *i)
{
	int	j;

	while (map->map[*i])
	{
		j = 0;
		while (map->map[*i][j])
		{
			if (map->map[*i][j] != ' ' && map->map[*i][j] != '1'
					&& map->map[*i][j] != '0' && (map->map[*i][j] != 'N'
				&& map->map[*i][j] != 'S' && map->map[*i][j] != 'E'
				&& map->map[*i][j] != 'W'))
				return (ft_putstr_fd("Error : invalid character\n", 2), ft_free_all(map), exit(2));
			// if (map->map[*i][j] == 'N' || map->map[*i][j] == 'S' || map->map[*i][j] == 'E'
			// 	|| map->map[*i][j] == 'W')
				
			j++;
		}
		(*i)++;
	}
}



// map->height = ft_lstsize(map->lst_map) - *i;



