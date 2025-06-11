/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:56:30 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:56:31 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_in_map(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= map->width)
		return (2);
	return (1);
}

void	my_put_pixel(t_img *img, int y, int x, int color)
{
	char	*ptr;

	ptr = img->data_img + ((y * img->width) + (x * (img->height / 8)));
	*(int *)ptr = color;
}

void	check_end_game(t_var *var, t_player *player)
{
	if (var->map->tab_map[(int)(player->pos_y)][(int)(player->pos_x)] == 'X')
		var->exit = 1;
}

int	check_time(t_var *var)
{
	gettimeofday(&var->tv, NULL);
	if (var->tv.tv_sec - var->start_t < GAME_DURATION / 3)
		draw_img_in_img(var, var->batterie[0], var->width - 160, 0);
	else if (var->tv.tv_sec - var->start_t < ((double)GAME_DURATION * 0.666666))
		draw_img_in_img(var, var->batterie[1], var->width - 160, 0);
	else if (var->tv.tv_sec - var->start_t < GAME_DURATION)
		draw_img_in_img(var, var->batterie[2], var->width - 160, 0);
	if (var->tv.tv_sec - var->start_t >= GAME_DURATION)
	{
		var->end_g = 1;
		return (1);
	}
	return (0);
}
