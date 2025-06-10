#include "cub3D.h"

void	set_timer(t_var* var)
{
	gettimeofday(&var->tv, NULL);
	var->start_t = var->tv.tv_sec;
	var->batterie = malloc(sizeof(t_img) * 3);
	var->batterie[0].img = mlx_xpm_file_to_image(var->mlx, "batterie3.xpm", var->batterie[0].width, var->batterie[0].height);
	var->batterie[1].img = mlx_xpm_file_to_image(var->mlx, "batterie2.xpm", var->batterie[1].width, var->batterie[1].height);
	var->batterie[2].img = mlx_xpm_file_to_image(var->mlx, "batterie1.xpm", var->batterie[2].width, var->batterie[2].height);
	var->batterie[0].data_img = mlx_get_data_addr(var->batterie[0].img, &var->batterie[0].bpp, &var->batterie[0].line_len, &var->batterie[0].endian);
	var->batterie[1].data_img = mlx_get_data_addr(var->batterie[1].img, &var->batterie[1].bpp, &var->batterie[1].line_len, &var->batterie[1].endian);
	var->batterie[2].data_img = mlx_get_data_addr(var->batterie[2].img, &var->batterie[2].bpp, &var->batterie[2].line_len, &var->batterie[2].endian);
}

int main(int argc, char **argv)
{
	t_var	var; 

	var.player = NULL;
	var.cast = NULL;
	var.img = NULL;
	var.img_g = NULL;
	var.minimap = NULL;
	ft_parse(argc, argv, &var);
	// printf("g to m %f\n", var.map->g_to_m);
	var.height = 800;
	var.width = 1200;
	var.time = 500;
	var.count = 0;
	var.on_off = 1;
	var.a = 4;
	set_timer(&var);
	setup_window(&var);
	ft_free_all(&var);
	return (0);
}
