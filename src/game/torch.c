/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:54:04 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:54:05 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	find_coeff(t_var *var, t_img image)
{
	if (image.img == var->torch[0].img || image.img == var->torch[1].img
		|| image.img == var->torch[2].img || image.img == var->torch[3].img
		|| var->torch[4].img || image.img == var->torch[5].img)
	{
		if (var->on_off == -1)
			return (0.4);
		else
			return (0.8);
	}
	return (1);
}

void	draw_img_in_img(t_var *var, t_img image, int sx, int sy)
{
	int		x;
	int		y;
	int		scl;

	y = -1;
	scl = 2;
	if (image.img == var->gameover.img || image.img == var->victory.img)
		scl = 4;
	while (++y + sy < var->height && y < image.height * scl)
	{
		x = -1;
		while (++x + sx < var->width && x < image.width * scl)
		{
			var->light->colo = *(int *)(image.data_img
					+ (y / scl * image.line_len) + (x / scl * (image.bpp / 8)));
			if ((var->light->colo >> 24 & 0xFF) == 0)
			{
				var->light->coeff = find_coeff(var, image);
				var->light->colo = shadow(var->light->colo, var->light->coeff);
				*(int *)(var->img_g->data_img + (sx + x) * (var->img_g->height
							/ 8) + (sy + y) * var->img_g->width)
					= var->light->colo;
			}
		}
	}
}

void	open_close_d(t_var *var, t_map *map)
{
	double	anticip_x;
	double	anticip_y;

	anticip_y = var->player->pos_y + var->player->dir_y;
	anticip_x = var->player->pos_x + var->player->dir_x;
	if (var->player->o_c_door == 1)
	{
		if (map->tab_map[(int)(anticip_y)][(int)(anticip_x)] == 'D')
			map->tab_map[(int)(anticip_y)][(int)(anticip_x)] = 'O';
		else if (map->tab_map[(int)(var->player->pos_y)]
			[(int)(var->player->pos_x)] != 'O'
			&& map->tab_map[(int)(anticip_y)][(int)(anticip_x)] == 'O')
			map->tab_map[(int)(anticip_y)][(int)(anticip_x)] = 'D';
	}
	var->player->o_c_door = 0;
}
