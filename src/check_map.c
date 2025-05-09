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

t_player	*init_player(t_var *var, int x, int y)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->game_x = (float)(x * 64);
	player->game_y = (float)(y * 64);
	player->map_x = (float)((x + 0.25) * 20);
	player->map_y = (float)((y + 0.25) * 20);
	if (var->map->tab_map[x][y] == 'N')
		player->dir = radian(NORTH);
	if (var->map->tab_map[x][y] == 'S')
		player->dir = radian(SOUTH);
	if (var->map->tab_map[x][y] == 'E')
		player->dir = radian(EAST);
	if (var->map->tab_map[x][y] == 'W')
		player->dir = radian(WEAST);
	player->fov = radian(45);
	return (player);
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
		if (ft_strrchr(map->tab_file[*i], '1') == NULL)
		{
			map->tab_map[k] = NULL;
			break;
		}
		if (map->tab_file[*i])
			map->tab_map[k] = ft_strdup(map->tab_file[*i]);
		else
			return ;
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
	int	check;
	(void) var;

	i = -1;
	check = 0;
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
				if (check != 0)
					return (ft_putstr_fd("Error : should have only one "
					"player\n", 2), ft_free_all(map), exit(2));
				var->player = init_player(var, i, j);
				check = 1;
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
	int		len;

	i = 0;
	while (map->tab_map[i])
	{
		line = ft_strrchr(map->tab_map[i], '1');
		if (line == NULL)
			return (ft_putstr_fd("Error : invalid map (missing wall)", 2),
				ft_free_all(map), exit(1));
		if (ft_strlen(line) > 1 && map->tab_map[i] != NULL)
		{
			temp = ft_strdup(map->tab_map[i]);
			len = (int)ft_strlen(temp) - (int)ft_strlen(line) + 1;
			free (map->tab_map[i]);
			map->tab_map[i] = ft_substr(temp, 0, len);
			free (temp);
		}
		if ((int)ft_strlen(map->tab_map[i]) > map->width)
			map->width = ft_strlen(map->tab_map[i]);
		i++;
	}
	map->height = i;
}

int	check_horizontal(char *tab)
{
	int	j;

	j = 0;
	// while (ft_check_space(tab[j] == 0))
	// 	j++;
	while (tab[j] && tab[j] == '1')
		j++;
	if (tab[j])
		return (1);
	return (0);
}

int	check_vertical(t_map *map)
{
	int	i;
	
	i = 1;
	while (i < map->height)
	{
		if (map->tab_map[i][0] != '1' 
			|| map->tab_map[i][ft_strlen(map->tab_map[i] - 1)] != '1')
			return (ft_putstr_fd("Error : invalid map (missing wall)", 2),
				ft_free_all(map), exit(1), 1);
		i++;
	}
	return (0);
}

int	count_empty(char **tab)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	floodfill_space(t_map *map, char **temp, int x, int y)
{
	if ((x < 0 || x > map->height) || (y < 0 || !map->tab_map[x][y]))
		return ;
	if (temp[x][y] != '1')
		temp[x][y] = '1';
	else
		return ;
	floodfill_space(map, temp, x + 1,  y);
	floodfill_space(map, temp, x - 1,  y);
	floodfill_space(map, temp, x,  y + 1);
	floodfill_space(map, temp, x,  y - 1);
}


void	check_wall(t_map *map)
{
	int		count;
	int		i;
	int		j;
	char	**temp;

	temp = map->tab_map;
	if (check_horizontal(map->tab_map[0]) == 0 
		&& check_horizontal(map->tab_map[map->height -1]) == 0 && check_vertical(map) == 0)
		return ;
	else
	{
		i = 0;
		count = count_empty(map->tab_map);
		while (temp[i])
		{
			j = 0;
			while (temp[i][j])
			{
				if (ft_check_space(temp[i][j]) == 0)
					floodfill_space(map, temp, 0, 0);
				j++;
			}
			ft_print_tab(temp);
			i++;
			printf("\nnext\n");
		}
		if (count != count_empty(temp))
			return (ft_putstr_fd("Error : invalid map (missing wall)", 2),
			ft_free_all(map), exit(1));
	}
	printf("map ok\n");
}

void	add_space_end(t_map *map)
{
	int		i;
	int		j;
	char	*space;
	char	*temp;

	i = 0;
	space = NULL;
	while (map->tab_map[i])
	{
		if ((int)ft_strlen(map->tab_map[i]) < map->width)
		{
			j = 0;
			while (map->tab_map[i][j])
				j++;
			space = malloc(map->width - j + 1 * sizeof (char));
			ft_memset(space, ' ', map->width - j);
			temp = map->tab_map[i];
			map->tab_map[i] = ft_strjoin(temp, space);
			free (temp);
			free (space);
		}
		i++;
	}
}

void	check_map(t_var *var, int *i)
{
	stock_map_in_tab(var->map, i);
	delete_space(var->map);
	ft_check_ascii(var, var->map);
	// add_space_end(var->map);
	// check_wall(var->map);
	ft_print_tab(var->map->tab_map);
	// parse_all_map(var, var->player->x,var->player->y);
//  et toute la map
}

// map->height = ft_lstsize(map->lst_map) - *i;



