/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:53:48 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/11 15:53:49 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	select_light_coeff(t_var *var, t_light *light, int i)
{
	if (i < var->height / 2)
	{
		light->coeff = 1.f - (double)i / (double)((var->height - 1) / 2);
		if (light->coeff > 0.45)
			light->coeff = 0.45;
		light->colo = var->map->color_c;
	}
	else
	{
		light->coeff = ((double)(i - var->height / 2))
			/ ((var->height / 2) - 1) + 0.1;
		light->colo = var->map->color_f;
	}
}

void	draw_game(t_var *var, t_img *img_g, t_light *light)
{
	int		x;
	int		i;
	double	x_left;
	double	x_right;

	x = 0;
	while (x < var->width)
	{
		i = 0;
		while (i < var->height)
		{
			select_light_coeff(var, light, i);
			x_left = light->left_b + (i - light->bottom) * (light->left_top
					- light->left_b) / (double)(light->top - light->bottom);
			x_right = light->right_b + (i - light->bottom) * (light->right_top
					- light->right_b) / (double)(light->top - light->bottom);
			if ((i >= light->top && (x < x_left || x > x_right)))
				light->coeff = 0.15;
			if (var->on_off == -1)
				light->coeff = 0;
			my_put_pixel(img_g, i, x, shadow(light->colo, light->coeff));
			i++;
		}
		x++;
	}
}

void	draw_one_wall_pixel(t_var *var, t_cast *cast, int i, int y)
{
	double	x_left;
	double	x_right;
	double	ratio_y;

	var->light->colo = *((int *)(cast->texture.data_img + (cast->text_pos_y
					* cast->texture.line_len)
				+ (cast->text_pos_x * cast->texture.bpp / 8)));
	var->light->coeff = expf(-cast->dist * 0.2f);
	ratio_y = (y - var->light->bottom)
		/ (double)(var->light->top - var->light->bottom);
	x_left = var->light->left_b + ratio_y
		* (var->light->left_top - var->light->left_b);
	x_right = var->light->right_b + ratio_y
		*(var->light->right_top - var->light->right_b);
	if ((y >= var->light->top && (i < x_left || i > x_right)))
		var->light->coeff = 0.1;
	if (var->on_off == -1)
		var->light->coeff = 0;
	var->light->colo = shadow(var->light->colo, var->light->coeff);
	if ((var->light->colo >> 24 & 0xFF) == 0)
		my_put_pixel(var->img_g, (int)y, i, var->light->colo);
}

void	draw_wall(t_var *var, t_cast *cast, int i)
{
	double	y;
	double	y_end;
	double	step;

	y = -cast->wall_h / 2.0f + var->height / 2.0f;
	y_end = cast->wall_h / 2.0f + var->height / 2.0f;
	if (y < 0)
		y = 0;
	if (y_end >= var->height)
		y_end = var->height - 1;
	step = (double)cast->texture.height / (cast->wall_h);
	cast->double_text_pos_y = (y - var->height / 2 + cast->wall_h / 2) * step;
	while (y < y_end)
	{
		if (cast->double_text_pos_y < 0)
			cast->double_text_pos_y = 0;
		if (cast->double_text_pos_y >= cast->texture.height)
			cast->double_text_pos_y = cast->texture.height - 1;
		cast->text_pos_y = (int)cast->double_text_pos_y;
		draw_one_wall_pixel(var, cast, i, y);
		cast->double_text_pos_y += step;
		y++;
	}
}

void	make_game(t_var *var)
{
	var->img_g = init_img();
	var->img_g->img = mlx_new_image(var->mlx, (int)var->width,
			(int)var->height);
	var->img_g->data_img = mlx_get_data_addr(var->img_g->img,
			&var->img_g->height, &var->img_g->width, &var->img_g->endian);
}
