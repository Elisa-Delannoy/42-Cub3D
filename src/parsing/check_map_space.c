#include "cub3D.h"

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
			if (tab[i] == 'N' || tab[i] == 'S' || tab[i] == 'E'
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

int	check_space_in_map(t_var *var, int i, int *j)
{
	int		count;
	char	**temp;

	if (var->map->tab_map[i][*j] != ' ')
		return (0);
	if (*j == 0 && var->map->tab_map[i][*j] == ' ')
	{
		while (var->map->tab_map[i][*j] == ' '
			&& (var->map->tab_map[i][*j + 1] == ' '
			|| var->map->tab_map[i][*j + 1] == '1'))
			(*j)++;
	}
	else if (var->map->tab_map[i][*j] == ' ')
	{
		temp = tab_cpy(var->map->tab_map, var->map->height);
		count = count_empty(var->map->tab_map);
		floodfill_space(var->map, temp, i, *j);
		if (count != count_empty(temp))
			return (ft_putstr_fd("Error : invalid character\n", 2),
				ft_free_all(var), free_split(temp), exit(1), 1);
		free_split(temp);
	}
	return (*j);
}
