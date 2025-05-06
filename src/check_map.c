#include "../cub3D.h"

// void	parse_all_map(t_var *var, int x, int y)
// {
// 	if (var->map->tab_map[x][y] == '0')
// 	{
// 		var->map->tab_map[x][y] == '1';
// 	}
// 	else
// 		return ;
// 	parse_all_map(&var, x + 1, y);
// 	parse_all_map(&var, x - 1, y);
// 	parse_all_map(&var, x, y + 1);
// 	parse_all_map(&var, x, y - 1);
// }

float	radian(int degree)
{
	return (degree * PI / 180);
}

void	init_player(t_var *var, int x, int y)
{
	var->player->game_x = (float)(x * 64);
	var->player->game_y = (float)(y * 64);
	var->player->map_x = (float)((x + 0.25) * 20);
	var->player->map_y = (float)((y + 0.25) * 20);
	if (var->map->tab_map[x][y] == 'N')
		var->player->dir = radian(NORTH);
	if (var->map->tab_map[x][y] == 'S')
		var->player->dir = radian(SOUTH);
	if (var->map->tab_map[x][y] == 'E')
		var->player->dir = radian(EAST);
	if (var->map->tab_map[x][y] == 'W')
		var->player->dir = radian(WEAST);
	var->player->fov = radian(90);
}


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

void	ft_check_ascii(t_var *var, t_map *map)
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
			if ((map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S' || map->tab_map[i][j] == 'E'
				|| map->tab_map[i][j] == 'W'))
				init_player(var, i, j);
				/*rajouter conditon if posiition alors donner la psoition || compteur pos, si > 1 erreur*/				
			j++;
		}
		i++;
	}
}

void	check_map(t_var *var, int *i)
{
	stock_map_in_tab(var->map, i);
	ft_check_ascii(var, var->map);
	printf("map ok");
	ft_print_tab(var->map->f);
	// parse_all_map(var, var->player->x,var->player->y);
// check nom debut, et toute la map
}

// map->height = ft_lstsize(map->lst_map) - *i;



