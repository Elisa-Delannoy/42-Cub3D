#include "cub3D.h"

// float	distance(t_point cell, float x0, float y0)
// {
// 	return (sqrt(((cell.x - x0) * (cell.x - x0))
// 			+ ((cell.y - y0) * (cell.y - y0))));
// }

// int	valid_point(t_var *var, t_point cell)
// {
// 	if ((cell.y > 0  && cell.x > 0)
// 		&& (cell.x < (float)var->map->width * GAME_sz
// 		&& cell.y < (float)var->map->height * GAME_sz))
// 		return (0);
// 	return (1);
// }


// int	check_aroud(t_map *map, float new_y, float new_x)
// {

// 	if ((new_y + 0.1f) > map->height || (new_y - 0.1) < 0
// 		|| (int)((new_x - 0.1) / GAME_sz) < 0 || (int)((new_x + 0.1f) / GAME_sz) > map->width)
// 		return (0);
// 	if (map->tab_map[(int)((new_y + 0.1) / GAME_sz)][(int)(new_x / GAME_sz)] == '1')
// 		return (1);
// 	if (map->tab_map[(int)((new_y - 0.1) / GAME_sz)][(int)(new_x / GAME_sz)] == '1')
// 		return (1);
// 	if (map->tab_map[(int)(new_y / GAME_sz)][(int)((new_x - 0.1) / GAME_sz)] == '1')
// 		return (1);
// 	if (map->tab_map[(int)(new_y / GAME_sz)][(int)((new_x + 0.1) / GAME_sz)] == '1')
// 		return (1);
// 	else
// 		return (0);
// }


// int check_raycasting(float new_y, float new_x, t_var *var)
// {
// 	if (new_y < 0  ||new_x < 0 || new_x >= var->map->width || new_y >= var->map->height)
// 		return (0);
// 	if (var->map->tab_map[(int)new_y][(int)new_x] == '1')
// 		return (0);
// 		// && (var->map->tab_map[(int)new_y][(int)new_x] == '1' || check_aroud(var->map, new_y, new_x) == 1))
// 	else
// 		return (1);
// }
