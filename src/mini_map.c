#include "../cub3D.h"

void	draw_player(t_img *img, int color, int i, int y)
{
	int save_i;
	int save_y;
	char *ptr;
	
	save_i = i;
	save_y = y;
	while (y > save_y - 10)
	{
		i = save_i;
		while (i-- > save_i - 10)
		{
			ptr = img->data_img + ((y * img->size_line) + (i * (img->bits_per_pixel / 8)));
			*(int *)ptr = color;
		}
		y--;
	}
}

void	draw_map(t_img *img, int color, int i, int y)
{
	int save_i;
	int save_y;
	char *ptr;

	save_i = i;
	save_y = y;
	while (y < save_y + 20)
	{
		i = save_i;
		while (i++ < save_i + 20) /*largeur map*/
		{
			ptr = img->data_img + ((y * img->size_line) + (i * (img->bits_per_pixel / 8)));
			*(int *)ptr = color;
		}
		y++;
	}
}

void	make_minimap(t_var *var)
{
	int i;
	int y;

	y = 0;
	var->img = init_img();
	var->img->img = mlx_new_image(var->mlx, 1920, 1080);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->bits_per_pixel, &var->img->size_line, &var->img->endian);
	while (var->map->tab_map[y])
	{
		i = 0;
		while (var->map->tab_map[y][i])
		{
			if (var->map->tab_map[y][i] == '1')
				draw_map(var->img, 255, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			else if (var->map->tab_map[y][i] == '0')
				draw_map(var->img, 125, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			else if (var->map->tab_map[y][i] != ' ')
				draw_map(var->img, 125, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			i++;
		}
		y++;
	}
	
}
