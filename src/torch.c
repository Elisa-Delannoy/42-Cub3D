#include "cub3D.h"

t_img	*init_torch(t_var *var)
{
	t_img	*torch;

	torch = malloc(sizeof(t_img) * 5);
	torch[4].img = mlx_xpm_file_to_image(var->mlx,
		"torch1.xpm", &torch[4].width, &torch[4].height);
	torch[3].img = mlx_xpm_file_to_image(var->mlx,
		"torch2.xpm", &torch[3].width, &torch[3].height);
	torch[2].img = mlx_xpm_file_to_image(var->mlx,
		"torch3.xpm", &torch[2].width, &torch[2].height);
	torch[1].img = mlx_xpm_file_to_image(var->mlx,
		"torch5.xpm", &torch[1].width, &torch[1].height);
	torch[0].img = mlx_xpm_file_to_image(var->mlx,
		"torch4.xpm", &torch[0].width, &torch[0].height);
	torch[4].data_img = mlx_get_data_addr(torch[4].img,
		&torch[4].bpp, &torch[4].line_len, &torch[4].endian);
	torch[3].data_img = mlx_get_data_addr(torch[3].img,
		&torch[3].bpp, &torch[3].line_len, &torch[3].endian);
	torch[2].data_img = mlx_get_data_addr(torch[2].img,
		&torch[2].bpp, &torch[2].line_len, &torch[2].endian);
	torch[1].data_img = mlx_get_data_addr(torch[1].img,
		&torch[1].bpp, &torch[1].line_len, &torch[1].endian);
	torch[0].data_img = mlx_get_data_addr(torch[0].img,
		&torch[0].bpp, &torch[0].line_len, &torch[0].endian);
	return(torch);
}



void	draw_img_in_img(t_var *var, t_img image, int start_x, int start_y)
{
	int x = 0;
	int y = 0;
	int color;
	int scale = 2;

	while (y < image.height * scale)
	{
		x = 0;
		while (x < image.width * scale)
		{
			int src_x = x / scale;
			int src_y = y / scale;

			color = *(int *)(image.data_img + (src_y * image.line_len) + (src_x * (image.bpp / 8)));
			if ((color >> 24 & 0xFF) == 0)
				*(int *)(var->img_g->data_img + (start_y + y) * var->img_g->width + (start_x + x) * (var->img_g->height / 8)) = color;
			x++;
		}
		y++;
	}
}

void	draw_img_end(t_var *var, t_img image, int start_x, int start_y)
{
	int x = 0;
	int y = 0;
	int color;
	int scale = 4;

	while (y < image.height * scale)
	{
		x = 0;
		while (x < image.width * scale)
		{
			int src_x = x / scale;
			int src_y = y / scale;

			color = *(int *)(image.data_img + (src_y * image.line_len) + (src_x * (image.bpp / 8)));
			if ((color >> 24 & 0xFF) == 0)
				*(int *)(var->img_g->data_img + (start_y + y) * var->img_g->width + (start_x + x) * (var->img_g->height / 8)) = color;
			x++;
		}
		y++;
	}
}

// void	draw_img_in_win(t_var *var, int i)
// {
// 	// ynt dest_w = 160;
// 	// ynt dest_h = 160;
// 	int start_x = 550; // marge gauche
// 	int start_y = 650; // en bas de la fenêtre
// 	int x = 0;
// 	int y = 0;
// 	int color;
// 	int scale = 2;

// 	while (y < var->torch[i].height * scale)
// 	{
// 		x = 0;
// 		while (x < var->torch[i].width * scale)
// 		{
// 			int src_x = x / scale;
// 			int src_y = y / scale;

// 			color = *(int *)(var->torch[i].data_img + (src_y * var->torch[i].line_len) + (src_x * (var->torch[i].bpp / 8)));
// 			if ((color >> 24 & 0xFF) == 0)
// 				*(int *)(var->img_g->data_img + (start_y + y) * var->img_g->width + (start_x + x) * (var->img_g->height / 8)) = color;
// 			x++;
// 		}
// 		y++;
// 	}
// }
