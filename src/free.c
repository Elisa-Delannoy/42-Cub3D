#include "cub3D.h"

int	clear_all(t_var *var)
{
	mlx_do_key_autorepeaton(var->mlx);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
	exit (EXIT_SUCCESS);
	return (0);
}

void	free_map(t_var *var)
{
	if (var->map)
	{
		if (var->map->lst_map)
			ft_lstclear(&var->map->lst_map, free);
		if (var->map->tab_file)
			free_split(var->map->tab_file);
		if (var->map->tab_map)
			free_split(var->map->tab_map);
		if (var->map->temp)
			free_split(var->map->temp);
		if (var->map->no)
			free(var->map->no);
		if (var->map->so)
			free(var->map->so);
		if (var->map->we)
			free(var->map->we);
		if (var->map->ea)
			free(var->map->ea);
		if (var->map->door)
			free(var->map->door);
		if (var->map->exit)
			free(var->map->exit);
		free(var->map);
	}
}

int	ft_free_all(t_var *var)
{
	free_map(var);
	if (var->player != NULL)
		free(var->player);
	if (var->cast != NULL)
		free(var->cast);
	if (var->light != NULL)
		free(var->light);
	if (var->minimap != NULL)
		free(var->minimap);
	if (var->img != NULL)
		free (var->img);
	if (var->img_g != NULL)
		free (var->img_g);
	re
}
