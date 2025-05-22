#include "cub3D.h"
#include "raycasting.h"


int	in_map(t_map *map, int x, int y)
{
	return (x >= 0 && y >= 0 && x < map->width && y < map->height);
}

int	check_collide(t_map *map, char *collide_set, int x, int y)
{
	return (! in_map(map, x, y) || ft_strchr(collide_set, map->tab_map[y][x]));
}

t_cast_data	calc_cast(t_point start, double angle)
{
	t_cast_data	data;

	data.start = start;
	data.angle = angle;
	data.tan_angle = tan(angle);
	data.step = (t_point){GAME_sz, GAME_sz};
	if (cos(angle) <= 0)
		data.step.x *= -1;
	if (sin(angle) <= 0)
		data.step.y *= -1;
	data.v_hit.x = floor(start.x / GAME_sz) * GAME_sz;
	if (data.step.x > 0)
		data.v_hit.x += GAME_sz;
	data.v_hit.y = start.y + (data.v_hit.x - start.x) * data.tan_angle;
	data.h_hit.y = floor(start.y / GAME_sz) * GAME_sz;
	if (data.step.y > 0)
		data.h_hit.y += GAME_sz;
	data.h_hit.x = start.x + (data.h_hit.y - start.y) / data.tan_angle;
	return (data);
}
int	check_vertical_hit(t_map *map, char *collide_set, t_cast_data *data,
	t_point *collide_cell)
{
	t_point	cell;

	cell.x = floor(data->v_hit.x / GAME_sz);
	cell.y = floor(data->v_hit.y / GAME_sz);
	if (data->step.x < 0)
		cell.x--;
	if (check_collide(map, collide_set, cell.x, cell.y))
	{
		if (collide_cell)
			*collide_cell = cell;
		return (1);
	}
	data->v_hit.x += data->step.x;
	data->v_hit.y += data->step.x * data->tan_angle;
	return (0);
}

int	check_horizontal_hit(t_map *map, char *collide_set, t_cast_data *data,
	t_point *collide_cell)
{
	t_point	cell;

	cell.x = floor(data->h_hit.x / GAME_sz);
	cell.y = floor(data->h_hit.y / GAME_sz);
	if (data->step.y < 0)
		cell.y--;
	if (check_collide(map, collide_set, cell.x, cell.y))
	{
		if (collide_cell)
			*collide_cell = cell;
		return (1);
	}
	data->h_hit.x += data->step.y / data->tan_angle;
	data->h_hit.y += data->step.y;
	return (0);
}

void	find_hit(t_map *map, char *collide_set, t_cast_data data, t_hit *hit)
{
	t_point	collide_cell;

	while (1)
	{
		if (fabs(data.v_hit.x - data.start.x)
			< fabs(data.h_hit.x - data.start.x))
		{
			if (check_vertical_hit(map, collide_set, &data, &collide_cell))
			{
				hit->axis = VERTICAL;
				hit->collide_cell = collide_cell;
				return (hit->pos = data.v_hit, (void)0);
			}
		}
		else
		{
			if (check_horizontal_hit(map, collide_set, &data, &collide_cell))
			{
				hit->axis = HORIZONTAL;
				hit->collide_cell = collide_cell;
				return (hit->pos = data.h_hit, (void)0);
			}
		}
	}
}

void	fill_hit_struct(t_hit *hit, t_point start)
{
	if (hit->axis == VERTICAL)
	{
		hit->col_index = (int)hit->pos.y % GAME_sz;
		if (hit->pos.x <= start.x)
			hit->side = D_WEST;
		else
			hit->side = D_EAST;
	}
	else
	{
		hit->col_index = (int)hit->pos.x % GAME_sz;
		if (hit->pos.y <= start.y)
			hit->side = D_NORTH;
		else
			hit->side = D_SOUTH;
	}
	if (hit->side == D_SOUTH || hit->side == D_WEST)
		hit->col_index = GAME_sz - 1 - hit->col_index;
}

t_hit	cast_ray(t_map *map, t_point start, double angle, char *collide_set)
{
	t_hit	hit;

	find_hit(map, collide_set, calc_cast(start, angle), &hit);
	printf("start.x %f\n", start.x /64 );
	printf("hit.pos.x %f\n", hit.pos.x/64);
	printf("start.y %f\n", start.y/64);
	printf("hit.pos.y %f\n", hit.pos.y/64);
	hit.distance = sqrt(pow(start.x - hit.pos.x, 2)
			+ pow(start.y - hit.pos.y, 2));
	printf("DISTANCE %f\n", hit.distance);
	fill_hit_struct(&hit, start);
	hit.collide_type = map->tab_map[(int)hit.collide_cell.y][(int)hit.collide_cell.x];
	return (hit);
}
