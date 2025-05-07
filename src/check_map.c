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
	var->player->fov = radian(45);
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
		if (ft_strrchr(map->tab_map[k], '1') == NULL)
			break;
		k++;
		(*i)++;
	}
	map->tab_map[k] = NULL;
}

int	check_space_in_map(t_map *map, int i, int j)
{
	if (map->tab_map[i][j] == ' ')
	{
		if (map->tab_map[i][j + 1] == ' ' || map->tab_map[i][j + 1] == '1')
			return (0);
	}
	return (1);
}

void	ft_check_ascii(t_var *var, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	var->player->game_x = -1;
	while (map->tab_map[++i])
	{
		j = 0;
		while (map->tab_map[i][j])
		{
			if (check_space_in_map(map, i, j) == 0 || (map->tab_map[i][j] == '1'
				|| map->tab_map[i][j] == '0'))
				j++;
			else if (map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S'
				|| map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W')
			{
				if (var->player->game_x != -1)
					return (ft_putstr_fd("Error : should have only one "
					"player\n", 2), ft_free_all(map), exit(2));
				init_player(var, i, j);
				j++;
			}
			else
				return (ft_putstr_fd("Error : invalid character\n", 2),
					ft_free_all(map), exit(2));
		}
	}
}

void	delete_space(t_map *map)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while (map->tab_map[i])
	{
		line = ft_strrchr(map->tab_map[i], '1');
		if (line == NULL)
			return (ft_putstr_fd("Error : invalid map (missing wall)", 2),
				ft_free_all(map), exit(1));
		if (ft_strlen(line) > 1)
		{
			temp = ft_strdup(map->tab_map[i]);
			free (map->tab_map[i]);
			map->tab_map[i] = ft_substr(temp, 0, ft_strlen(temp) - ft_strlen(line) + 1);
		}
		if ((int)ft_strlen(map->tab_map[i]) > map->width)
			map->width = ft_strlen(map->tab_map[i]);
		i++;
	}
	map->height = i;
}

// int	check_horizontal(char *tab)
// {
// 	int	j;

// 	j = 0;
// 	while (ft_check_space(tab[j] == 0))
// 		j++;
// 	while (tab[j] && tab[j] == '1')
// 		j++;
// 	if (tab[j])
// 		return (1);
// 	return (0);
// }

// int	check_vertical

// void	check_wall(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map->tab_map[i])
// 	{
// 		if (check_horizontal(map->tab_map[0]) != 0 
// 			|| check_horizontal(map->tab_map[map->height - 1] != 0))
// 			return ;
			
// }

void	check_map(t_var *var, int *i)
{
	stock_map_in_tab(var->map, i);
	delete_space(var->map);
	ft_check_ascii(var, var->map);
	ft_print_tab(var->map->tab_map);
	// parse_all_map(var, var->player->x,var->player->y);
//  et toute la map
}

// map->height = ft_lstsize(map->lst_map) - *i;



