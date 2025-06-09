#include "cub3D.h"

t_img	*init_torch(t_var *var)
{
	t_img	*torch;

	torch = malloc(sizeof(t_img) * 3);
	torch[0].img = mlx_xpm_file_to_image(var->mlx,
		"torch1.xpm", &torch[0].width, &torch[0].height);
	torch[1].img = mlx_xpm_file_to_image(var->mlx,
		"torch2.xpm", &torch[0].width, &torch[0].height);
	torch[2].img = mlx_xpm_file_to_image(var->mlx,
		"torch3.xpm", &torch[0].width, &torch[0].height);
	torch[0].data_img = mlx_get_data_addr(torch[0].img,
		&torch[0].bpp, &torch[0].line_len, &torch[0].endian);
	torch[1].data_img = mlx_get_data_addr(torch[0].img,
		&torch[0].bpp, &torch[0].line_len, &torch[0].endian);
	torch[2].data_img = mlx_get_data_addr(torch[0].img,
		&torch[0].bpp, &torch[0].line_len, &torch[0].endian);
	return(torch);
}

void	draw_torch(t_var *var)
{
	// ynt dest_w = 160;
	// ynt dest_h = 160;
	int start_x = 550; // marge gauche
	int start_y = 650; // en bas de la fenêtre
	int x = 0;
	int y = 0;
	int color;
	int scale = 2;

	while (y < var->torch[0].height * scale)
	{
		x = 0;
		while (x < var->torch[0].width * scale)
		{
			int src_x = x / scale;
			int src_y = y / scale;

			color = *(int *)(var->torch[0].data_img + (src_y * var->torch[0].line_len) + (src_x * (var->torch[0].bpp / 8)));
			
			if ((color >> 24 & 0xFF) == 0)
				*(int *)(var->img_g->data_img + (start_y + y) * var->img_g->width + (start_x + x) * (var->img_g->height / 8)) = color;
			x++;
		}
		y++;
	}
}