#include "cub3D.h"

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
	var.height = 1200;
	var.width = 1900;
	var.time = 300;
	var.count = 0;
	setup_window(&var);
	ft_free_all(&var);
	return (0);
}
