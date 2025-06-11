#include "cub3D.h"

void	check_coordinate(t_var *var, char **dir, int i, int *j)
{
	int		fd;
	char	*path;

	*j = *j + 2;
	fd = 0;
	while (ft_check_space (var->map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(var->map, i, j);
	if (path)
	{
		if (*dir == NULL)
			*dir = ft_strdup(path);
		free(path);
		fd = open(*dir, O_RDONLY);
	}
	if (fd == -1 || *dir == NULL || (*dir)[ft_strlen(*dir) - 1] == '/')
		return (ft_putstr_fd("Error: invalid texture ", 2),
			ft_putendl_fd(*dir, 2), ft_free_all(var), exit(1));
}

int	ft_is_coordinates(t_var *var, t_map *map, int i, int *j)
{
	if (map->tab_file[i][*j] && map->tab_file[i][*j + 1]
		&& map->tab_file[i][*j + 2] == ' ')
	{
		if (map->tab_file[i][*j] == 'N' && map->tab_file[i][*j + 1] == 'O')
			return (map->c_no++, check_coordinate(var, &map->no, i, j), 0);
		else if (map->tab_file[i][*j] == 'S' && map->tab_file[i][*j + 1] == 'O')
			return (map->c_so++, check_coordinate(var, &map->so, i, j), 0);
		else if (map->tab_file[i][*j] == 'W' && map->tab_file[i][*j + 1] == 'E')
			return (map->c_we++, check_coordinate(var, &map->we, i, j), 0);
		else if (map->tab_file[i][*j] == 'E' && map->tab_file[i][*j + 1] == 'A')
			return (map->c_ea++, check_coordinate(var, &map->ea, i, j), 0);
		else
			return (1);
	}
	return (2);
}
