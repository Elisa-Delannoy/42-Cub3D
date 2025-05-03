#include "../cub3D.h"

void	ft_check_ascii(t_map *map, int *i)
{
	int	j;

	while (map->tab_file[*i])
	{
		j = 0;
		while (map->tab_file[*i][j])
		{
			if (map->tab_file[*i][j] != ' ' && map->tab_file[*i][j] != '1'
					&& map->tab_file[*i][j] != '0' && (map->tab_file[*i][j] != 'N'
				&& map->tab_file[*i][j] != 'S' && map->tab_file[*i][j] != 'E'
				&& map->tab_file[*i][j] != 'W'))
				return (ft_putstr_fd("Error : invalid character\n", 2), ft_free_all(map), exit(2));
			// if (map->tab_file[*i][j] == 'N' || map->tab_file[*i][j] == 'S' || map->tab_file[*i][j] == 'E'
			// 	|| map->tab_file[*i][j] == 'W')
				
			j++;
		}
		(*i)++;
	}
}



// map->height = ft_lstsize(map->lst_map) - *i;



