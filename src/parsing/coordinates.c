#include "cub3D.h"

// void	check_coordinate(t_var *var, char *dir, int i, int *j)
// {
// 	int		fd;
// 	char	*path;

// 	*j = *j + 2;
// 	fd = 0;
// 	while (ft_check_space (var->map->tab_file[i][*j]) == 0)
// 		(*j)++;
// 	path = check_texture(var->map, i, j);
// 	if (path)
// 	{
// 		if (dir == NULL)
// 			dir = ft_strdup(path);
// 		free(path);
// 		fd = open(dir, O_RDONLY);
// 	}
// 	if (fd == -1 || dir == NULL || dir[ft_strlen(dir) - 1] == '/')
// 		return (ft_putstr_fd("Error: invalid texture ", 2),
// 			ft_putendl_fd(dir, 2), ft_free_all(var), exit(1));
// }

void	no(t_var *var, t_map *map, int i, int *j)
{
	int		fd;
	char	*path;

	*j = *j + 2;
	fd = 0;
	map->c_no++;
	while (ft_check_space (map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(map, i, j);
	if (path)
	{
		if (map->no == NULL)
			map->no = ft_strdup(path);
		free(path);
		fd = open(map->no, O_RDONLY);
	}
	if (fd == -1 || map->no == NULL || map->no[ft_strlen(map->no) - 1] == '/')
		return (ft_putstr_fd("Error: invalid NO texture\n", 2),
			ft_free_all(var), exit(1));
}

void	so(t_var *var, t_map *map, int i, int *j)
{
	int		fd;
	char	*path;

	fd = 0;
	*j = *j + 2;
	map->c_so++;
	while (ft_check_space (map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(map, i, j);
	if (path)
	{
		if (map->so == NULL)
			map->so = ft_strdup(path);
		free(path);
		fd = open(map->so, O_RDONLY);
	}
	if (fd == -1 || map->so == NULL || map->so[ft_strlen(map->so) - 1] == '/')
		return (ft_putstr_fd("Error : invalid SO texture\n", 2),
			ft_free_all(var), exit(1));
}

void	ea(t_var *var, t_map *map, int i, int *j)
{
	int		fd;
	char	*path;

	fd = 0;
	*j = *j + 2;
	map->c_ea++;
	while (ft_check_space (map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(map, i, j);
	if (path)
	{
		if (map->ea == NULL)
			map->ea = ft_strdup(path);
		free(path);
		fd = open(map->ea, O_RDONLY);
	}
	if (fd == -1 || map->ea == NULL || map->ea[ft_strlen(map->ea) - 1] == '/')
		return (ft_putstr_fd("Error : invalid EA texture\n", 2),
			ft_free_all(var), exit(1));
}

void	we(t_var *var, t_map *map, int i, int *j)
{
	int		fd;
	char	*path;

	fd = 0;
	*j = *j + 2;
	map->c_we++;
	while (ft_check_space (map->tab_file[i][*j]) == 0)
		(*j)++;
	path = check_texture(map, i, j);
	if (path)
	{
		if (map->we == NULL)
			map->we = ft_strdup(path);
		free(path);
		fd = open(map->we, O_RDONLY);
	}
	if (fd == -1 || map->we == NULL || map->we[ft_strlen(map->we) - 1] == '/')
		return (ft_putstr_fd("Error : invalid WE texture\n", 2),
			ft_free_all(var), exit(1));
}

// int	ft_is_coordinates(t_var *var, t_map *map, int i, int *j)
// {
// 	if (map->tab_file[i][*j] && map->tab_file[i][*j + 1]
// 		&& map->tab_file[i][*j + 2] == ' ')
// 	{
// 		if (map->tab_file[i][*j] == 'N' && map->tab_file[i][*j + 1] == 'O')
// 			return (map->c_no++, check_coordinate(var, map->no, i, j), 0);
// 		else if (map->tab_file[i][*j] == 'S' && map->tab_file[i][*j + 1] == 'O')
// 			return (map->c_so++, check_coordinate(var, map->so, i, j), 0);
// 		else if (map->tab_file[i][*j] == 'W' && map->tab_file[i][*j + 1] == 'E')
// 			return (map->c_we++, check_coordinate(var, map->we, i, j), 0);
// 		else if (map->tab_file[i][*j] == 'E' && map->tab_file[i][*j + 1] == 'A')
// 			return (map->c_ea++, check_coordinate(var, map->ea, i, j), 0);
// 		else
// 			return (1);
// 	}
// 	return (2);
// }

int	ft_is_coordinates(t_var *var, t_map *map, int i, int *j)
{
	if (map->tab_file[i][*j] && map->tab_file[i][*j + 1]
		&& map->tab_file[i][*j + 2] == ' ')
	{
		if (map->tab_file[i][*j] == 'N' && map->tab_file[i][*j + 1] == 'O')
			return (no(var, map, i, j), 0);
		else if (map->tab_file[i][*j] == 'S' && map->tab_file[i][*j + 1] == 'O')
			return (so(var, map, i, j), 0);
		else if (map->tab_file[i][*j] == 'W' && map->tab_file[i][*j + 1] == 'E')
			return (we(var, map, i, j), 0);
		else if (map->tab_file[i][*j] == 'E' && map->tab_file[i][*j + 1] == 'A')
			return (ea(var, map, i, j), 0);
		else
			return (1);
	}
	return (2);
}
