#include "../cub3D.h"

void	draw(t_var *var, int color, int i, int y)
{
	int save_i;
	int save_y;

	save_i = i;
	save_y = y;
	while (y < save_y + 20)
	{
		i = save_i;
		while (i++ < save_i + 20) /*largeur map*/
			mlx_pixel_put(var->mlx, var->win, i, y, color);
		y++;
	}
}

void	make_minimap(t_var *var)
{
	int i;
	int y;
	
	y = 0;
	ft_print_tab(var->map);
	while (var->map->tab_map[y])
	{
		i = 0;
		while (var->map->tab_map[y][i])
		{
			if (var->map->tab_map[y][i] == '1')
				draw(var, 255, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			if (var->map->tab_map[y][i] == '0')
				draw(var, 0, 1920 - ((34 - i) * 20), 1080 - ((14 - y) * 20));
			i++;
		}
		y++;
	}
}
