#include "cub3D.h"

t_cast	*init_cast(void)
{
	t_cast	*cast;

	cast = malloc(sizeof(t_cast));
	return (cast);
}

t_img	*set_timer(t_var *var)
{
	t_img	*batterie;

	gettimeofday(&var->tv, NULL);
	var->start_t = var->tv.tv_sec;
	batterie = malloc(sizeof(t_img) * 5);
	batterie[0].img = mlx_xpm_file_to_image(var->mlx, "textures/batterie3.xpm",
			&batterie[0].width, &batterie[0].height);
	batterie[1].img = mlx_xpm_file_to_image(var->mlx, "textures/batterie2.xpm",
			&batterie[1].width, &batterie[1].height);
	batterie[2].img = mlx_xpm_file_to_image(var->mlx, "textures/batterie1.xpm",
			&batterie[2].width, &batterie[2].height);
	batterie[0].data_img = mlx_get_data_addr(batterie[0].img, &batterie[0].bpp,
			&batterie[0].line_len, &batterie[0].endian);
	batterie[1].data_img = mlx_get_data_addr(batterie[1].img, &batterie[1].bpp,
			&batterie[1].line_len, &batterie[1].endian);
	batterie[2].data_img = mlx_get_data_addr(batterie[2].img, &batterie[2].bpp,
			&batterie[2].line_len, &batterie[2].endian);
	return (batterie);
}

t_img	*init_torch(t_var *var)
{
	t_img	*torch;

	torch = malloc(sizeof(t_img) * 5);
	torch[4].img = mlx_xpm_file_to_image(var->mlx,
			"textures/torch1.xpm", &torch[4].width, &torch[4].height);
	torch[3].img = mlx_xpm_file_to_image(var->mlx,
			"textures/torch2.xpm", &torch[3].width, &torch[3].height);
	torch[2].img = mlx_xpm_file_to_image(var->mlx,
			"textures/torch3.xpm", &torch[2].width, &torch[2].height);
	torch[1].img = mlx_xpm_file_to_image(var->mlx,
			"textures/torch5.xpm", &torch[1].width, &torch[1].height);
	torch[0].img = mlx_xpm_file_to_image(var->mlx,
			"textures/torch4.xpm", &torch[0].width, &torch[0].height);
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
	return (torch);
}

void	init_img_end(t_var *var)
{
	var->gameover.img = mlx_xpm_file_to_image(var->mlx, "textures/gameover.xpm",
			&var->gameover.width, &var->gameover.height);
	var->gameover.data_img = mlx_get_data_addr(var->gameover.img,
			&var->gameover.bpp, &var->gameover.line_len, &var->gameover.endian);
	var->victory.img = mlx_xpm_file_to_image(var->mlx, "textures/victory.xpm",
			&var->victory.width, &var->victory.height);
	var->victory.data_img = mlx_get_data_addr(var->victory.img,
			&var->victory.bpp, &var->victory.line_len, &var->victory.endian);
	var->icon.img = mlx_xpm_file_to_image(var->mlx, "textures/icon.xpm",
			&var->icon.width, &var->icon.height);
	var->icon.data_img = mlx_get_data_addr(var->icon.img, &var->icon.bpp,
			&var->icon.line_len, &var->icon.endian);
}

void	make_minimap(t_var *var)
{
	var->img->img = mlx_new_image(var->mlx, 10 * MAP_sz, 10 * MAP_sz);
	var->img->data_img = mlx_get_data_addr(var->img->img, &var->img->height,
			&var->img->width, &var->img->endian);
}
