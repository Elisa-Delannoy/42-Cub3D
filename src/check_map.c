#include "../cub3D.h"

void	stock_map_in_tab(t_map *map, int *i)
{
	int	k;

	k = 0;
	map->tab_map = malloc((ft_lstsize(map->lst_map) + 1 - *i) * sizeof(char*));
	if (!map->tab_map)
		return (ft_free_all(map), exit(1));
	while (map->tab_file[*i])
	{
		map->tab_map[k] = ft_strdup(map->tab_file[*i]);
		k++;
		(*i)++;
	}
	map->tab_map[k] = NULL;
}

void	ft_check_ascii(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->tab_map[i])
	{
		j = 0;
		while (map->tab_map[i][j])
		{
			if (map->tab_map[i][j] != ' ' && map->tab_map[i][j] != '1'
					&& map->tab_map[i][j] != '0' && map->tab_map[i][j] != 32
				&& (map->tab_map[i][j] != 'N'
				&& map->tab_map[i][j] != 'S' && map->tab_map[i][j] != 'E'
				&& map->tab_map[i][j] != 'W'))
				return (ft_putstr_fd("Error : invalid character\n", 2),
					ft_free_all(map), exit(2));
				/*rajouter conditon if posiition alors donner la psoition || compteur pos, si > 1 erreur*/				
			j++;
		}
		i++;
	}
}

void	check_map(t_map *map, int *i)
{
	stock_map_in_tab(map, i);
	ft_check_ascii(map);
	printf("map ok");
	ft_print_tab(map->f);
// check nom debut, et toute la map
}

// map->height = ft_lstsize(map->lst_map) - *i;



