#include "cub3D.h"

t_img	*init_torch(t_var *var)
{
	t_img	*torch;

	torch = malloc(sizeof(t_img) * 2);
	torch[0].img = mlx_xpm_file_to_image(var->mlx,
		"torch1.xpm", &torch[0].width, &torch[0].height);
	torch[0].data_img = mlx_get_data_addr(torch[0].img,
		&torch[0].bpp, &torch[0].line_len, &torch[0].endian);
	return(torch);
}