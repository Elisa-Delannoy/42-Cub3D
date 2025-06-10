#include "cub3D.h"

void	door(t_var *var, t_map *map, int i, int *j)
{
	int		fd;
	char	*path;

	*j = *j + 2;
	fd = 0;
	map->c_d++;
	while (ft_check_space (map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(map, i, j);
	if (path)
	{
		if (map->door == NULL)
			map->door = ft_strdup(path);
		free(path);
		fd = open(map->door, O_RDONLY);
	}
	if (fd == -1 || map->door == NULL || map->door[ft_strlen(map->door) - 1] == '/')
		return (ft_putstr_fd("Error : invalid door texture\n", 2),
			ft_free_all(var), exit(1));
}

int	ft_is_door(t_var *var, t_map *map, int i, int *j)
{
	if (map->tab_file[i][*j] && map->tab_file[i][*j + 1]
		&& map->tab_file[i][*j + 2] == ' ')
	{
		if (map->tab_file[i][*j] == 'D' && map->tab_file[i][*j + 1] == 'O')
			door(var, map, i, j);
		else
			return (1);
		return (0);
	}
	return (2);
}

void	exit_d(t_var *var, t_map *map, int i, int *j)
{
	int		fd;
	char	*path;

	*j = *j + 2;
	fd = 0;
	map->c_x++;
	while (ft_check_space (map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(map, i, j);
	if (path)
	{
		if (map->exit == NULL)
			map->exit = ft_strdup(path);
		free(path);
		fd = open(map->exit, O_RDONLY);
	}
	if (fd == -1 || map->exit == NULL || map->exit[ft_strlen(map->exit) - 1] == '/')
		return (ft_putstr_fd("Error : invalid exit texture\n", 2),
			ft_free_all(var), exit(1));
}

int	ft_is_exit(t_var *var, t_map *map, int i, int *j)
{
	if (map->tab_file[i][*j] && map->tab_file[i][*j + 1]
		&& map->tab_file[i][*j + 2] == ' ')
	{
		if (map->tab_file[i][*j] == 'E' && map->tab_file[i][*j + 1] == 'X')
			exit_d(var, map, i, j);
		else
			return (1);
		return (0);
	}
	return (2);
}
