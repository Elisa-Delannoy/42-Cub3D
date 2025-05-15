#include "cub3D.h"

float	distance(t_point cell, float x0, float y0)
{
	return (sqrt(((cell.x - x0) * (cell.x - x0))
			+ ((cell.y - y0) * (cell.y - y0))));
}

int	valid_point(t_var *var, t_point cell, int type)
{
	if ((cell.y > 0  && cell.x > 0)
		&& (cell.x < var->map->width * (float)type
		&& cell.y < var->map->height * (float)type))
		return (0);
	return (1);
}

int check_raycasting(float new_y, float new_x, int type, t_var *var)
{
	if (new_y < 0  || new_x < 0 || new_x > var->map->width * type || new_y > var->map->height * type)
		return (0);
	if (var->map->tab_map[((int)new_y / type)] != 0
		&& var->map->tab_map[((int)new_y / type)][((int)new_x / type)] != 0
		&& var->map->tab_map[((int)new_y / type)][((int)new_x / type)] == '1')
		return (0);
	else
		return (1);
	return (1);
}
