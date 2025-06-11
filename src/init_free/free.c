/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:54:07 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 17:40:17 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_img(t_var *var)
{
	mlx_destroy_image(var->mlx, var->torch[0].img);
	mlx_destroy_image(var->mlx, var->torch[1].img);
	mlx_destroy_image(var->mlx, var->torch[2].img);
	mlx_destroy_image(var->mlx, var->torch[3].img);
	mlx_destroy_image(var->mlx, var->torch[4].img);
	mlx_destroy_image(var->mlx, var->batterie[0].img);
	mlx_destroy_image(var->mlx, var->batterie[1].img);
	mlx_destroy_image(var->mlx, var->batterie[2].img);
	if (var->victory.img)
		mlx_destroy_image(var->mlx, var->victory.img);
	if (var->end.img)
		mlx_destroy_image(var->mlx, var->end.img);
	if (var->gameover.img)
		mlx_destroy_image(var->mlx, var->gameover.img);
	mlx_destroy_image(var->mlx, var->icon.img);
	mlx_destroy_image(var->mlx, var->no_t.img);
	mlx_destroy_image(var->mlx, var->so_t.img);
	mlx_destroy_image(var->mlx, var->ea_t.img);
	mlx_destroy_image(var->mlx, var->we_t.img);
	if (var->door_t.img)
		mlx_destroy_image(var->mlx, var->door_t.img);
	if (var->exit_t.img)
		mlx_destroy_image(var->mlx, var->exit_t.img);
	mlx_destroy_image(var->mlx, var->img->img);
	mlx_destroy_image(var->mlx, var->img_g->img);
}

void	clear_all(t_var *var)
{
	free_img(var);
	mlx_do_key_autorepeaton(var->mlx);
	mlx_destroy_window(var->mlx, var->win);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
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
	if (var->mlx)
		clear_all(var);
	if (var->player != NULL)
		free(var->player);
	if (var->batterie != NULL)
		free(var->batterie);
	if (var->torch != NULL)
		free(var->torch);
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
	exit(1);
	return (0);
}
