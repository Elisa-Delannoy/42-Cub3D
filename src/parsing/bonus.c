/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:07 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:56:08 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fd == -1 || map->door == NULL
		|| map->door[ft_strlen(map->door) - 1] == '/')
		return (ft_putstr_fd("Error: invalid door texture ", 2),
			ft_putendl_fd(map->door, 2), ft_free_all(var), exit(1));
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
	if (fd == -1 || map->exit == NULL
		|| map->exit[ft_strlen(map->exit) - 1] == '/')
		return (ft_putstr_fd("Error: invalid exit texture ", 2),
			ft_putendl_fd(map->exit, 2), ft_free_all(var), exit(1));
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

int	check_w_s_d(t_map *map, int i, int j)
{
	if (map->c_d == 1)
	{
		if (map->tab_map[i][j] == ' ' || map->tab_map[i][j] == '1'
				|| map->tab_map[i][j] == '0' || map->tab_map[i][j] == 'D')
			return (1);
	}
	if (map->c_d == 0)
	{
		if (map->tab_map[i][j] == ' ' || map->tab_map[i][j] == '1'
				|| map->tab_map[i][j] == '0')
			return (1);
	}
	if (map->c_x == 1)
	{
		if (map->tab_map[i][j] == ' ' || map->tab_map[i][j] == '1'
				|| map->tab_map[i][j] == '0' || map->tab_map[i][j] == 'X')
			return (1);
	}
	if (map->c_d == 0)
	{
		if (map->tab_map[i][j] == ' ' || map->tab_map[i][j] == '1'
				|| map->tab_map[i][j] == '0')
			return (1);
	}
	return (0);
}
