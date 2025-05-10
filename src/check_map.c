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

int	stock_map_in_tab(t_map *map, int *i)
{
	int	k;

	k = 0;
	map->tab_map = malloc((ft_lstsize(map->lst_map) + 1 - *i) * sizeof(char*));
	if (!map->tab_map)
		return (1);
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
		{
			map->tab_map[k] = NULL;
			return (0);
		}
		k++;
		(*i)++;
	}
	map->tab_map[k] = NULL;
	return (0);
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
				if (var->player != 0)
					return (ft_putstr_fd("Error : should have only one "
					"player\n", 2), ft_free_all(var), exit(2));
				var->player = init_player(var, i, j);
				j++;
			}
			else
				return (ft_putstr_fd("Error : invalid character\n", 2),
					ft_free_all(var), exit(2));
		}
	}
	if (var->player == NULL)
		return (ft_putstr_fd("Error : player is missing\n", 2), ft_free_all(var), exit(2));
}

int	check_ok_delete(char *tab)
{
	int	i;

	i = 1;
	if (tab == NULL)
			return (ft_putstr_fd("Error : invalid map (missing wall)", 2), 1);
	while (tab[i])
	{
		if (tab[i] == ' ')
			i++;
		else
		{
			if (tab[i] == 'N' || tab[i]== 'S' || tab[i] == 'E'
				|| tab[i] == 'W' || tab[i] == '0')
				return (ft_putstr_fd("Error : invalid map\n", 2), 1);
			else
				return (ft_putstr_fd("Error : invalid character\n", 2), 1);
		}
	}
	return (0);
}

int	delete_space(t_map *map)
{
	char	*line;
	char	*temp;
	int		i;
	int		len;

	i = 0;
	while (map->tab_map[i])
	{
		line = ft_strrchr(map->tab_map[i], '1');
		if (check_ok_delete(line) == 1)
			return (1);
		// if (line == NULL)
		// 	return (ft_putstr_fd("Error : invalid map (missing wall)", 2), 1);
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
	return (0);
}

int	check_horizontal(char *tab, char c, char d)
{
	int	j;

	j = 0;
	while (tab[j] && (tab[j] == c || tab[j] == d))
		j++;
	if (tab[j])
		return (1);
	return (0);
}

int	check_vertical(t_map *map, int j, char c)
{
	int	i;

	i = 1;
	while (i < map->height)
	{
		j = 0;
		if (c == ' ')
		{
			while (map->tab_map[i][j] == ' ')
				j++;
		}
		if (map->tab_map[i][j] != '1' 
			|| map->tab_map[i][ft_strlen(map->tab_map[i]) - 1] != '1')
			return (1);
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
	if ((x < 0 || x >= map->height) || (y < 0 || y >= map->width))
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


int	check_wall_min_max(t_var *var)
{
	if (check_horizontal(var->map->tab_map[0], '1', '1') == 0 
		&& check_horizontal(var->map->tab_map[var->map->height -1], '1', '1') == 0
		&& check_vertical(var->map, 0, '1') == 0)
		return (0);
	if (check_horizontal(var->map->tab_map[0], '1', ' ') != 0
		|| check_horizontal(var->map->tab_map[var->map->height - 1], '1', ' ') != 0
		|| check_vertical(var->map, 0, ' ') != 0)
			return (ft_putstr_fd("Error : invalid map (missing wall)\n", 2), ft_free_all(var), exit(1), 1);
	return (2);
}


int	check_wall(t_map *map)
{
	int		count;
	int		i;
	int		j;
	char	**temp;

	temp = map->tab_map;
	// if (check_horizontal(map->tab_map[0], '1', '1') == 0 
	// 	&& check_horizontal(map->tab_map[map->height -1], '1', '1') == 0 && check_vertical(map, 0, '1') == 0)
	// 	return (0);
	// else
	// {
		// if (check_horizontal(map->tab_map[0], '1', ' ') != 0 || check_vertical(map, 0, ' ') != 0)
		// 	return (ft_putstr_fd("Error : invalid map (missing wall)\n", 2), 1);
		i = 0;
		count = count_empty(map->tab_map);
		while (temp[i])
		{
			j = 0;
			while (temp[i][j])
			{
				if (ft_check_space(temp[i][j]) == 0)
					floodfill_space(map, temp, i, j);
				j++;
			}
			i++;
		}
		if (count != count_empty(temp))
			return (ft_putstr_fd("Error : invalid map (missing wall)\n", 2), 1);
	// }
	return (0);
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
			space = malloc((map->width - j + 1) * sizeof (char));
			ft_memset(space, ' ', map->width - j);
			space[map->width - j] = '\0';
			temp = map->tab_map[i];
			map->tab_map[i] = ft_strjoin(temp, space);
			free(temp);
			free(space);
		}
		i++;
	}
}

int	check_map(t_var *var, int *i)
{
	if (stock_map_in_tab(var->map, i) == 1)
		return (1);
	if (delete_space(var->map) == 1)
		return (1);
	// ft_print_tab(var->map->tab_map);
	ft_check_ascii(var, var->map);
	if (check_wall_min_max(var) != 0)
	{
		add_space_end(var->map);
		// ft_print_tab(var->map->tab_map);
		if (check_wall(var->map) == 1)
			return (1);
	}
	printf("map ok\n");
	// parse_all_map(var, var->player->x,var->player->y);
//  et toute la map
	return (0);
}

// map->height = ft_lstsize(map->lst_map) - *i;



