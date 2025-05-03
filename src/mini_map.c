#include "../cub3D.h"

// void	ft_create_image(t_var *var)
// {
// 	void	*img;

// 	img = mlx_new_image(var->mlx, 1920, 1080);
// 	var->img->data_img = mlx_get_data_addr(img, var->img->bits_per_pixel, var->img->size_line, var->img->endian);

// }

// void	ft_draw_pixel(t_img *img, int col, int x, int y)
// {
// 	char ptr;

// 	ptr = img->data_img + (y * img->size_line + x * img->bits_per_pixel);
// 	*(int *)ptr = col;
// }

void	draw(t_img *img, int color, int i, int y)
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
	void	*img;

	y = 0;
	var->img = init_img();
	img = mlx_new_image(var->mlx, 1920, 1080);
	var->img->data_img = mlx_get_data_addr(img, &var->img->bits_per_pixel, &var->img->size_line, &var->img->endian);
	while (var->map->tab_file[y])
	{
		i = 0;
		while (var->map->tab_file[y][i])
		{
			if (var->map->tab_file[y][i] == '1')
				draw(var->img, 255, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			if (var->map->tab_file[y][i] == '0')
				draw(var->img, 0, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			i++;
		}
		y++;
	}
	mlx_put_image_to_window(var->mlx, var->win, img, 0, 0);
}
