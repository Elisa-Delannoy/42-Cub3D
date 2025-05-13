#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define PI 3.14159265358979323846

typedef enum e_dir
{
	NORTH = 90,
	SOUTH = 270,
	EAST = 0,
	WEAST = 180,
	MAP = 20,
	GAME = 64
}	t_dir;

typedef enum e_key
{
	RIGHT = 100,
	LEFT = 97,
	UP = 119,
	DOWN = 115,
	TURN_L = 65361,
	TURN_R = 65363,
	ESC = 65307
}	t_key;

typedef struct s_player
{
	float	game_x;
	float	game_y;
	float	map_x;
	float	map_y;
	double	dir;
	float	fov;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*data_img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_map
{
	t_list	*lst_map;
	char	**tab_file;
	char	**tab_map;
	char	**temp;
	int		c_no;
	int		c_so;
	int		c_we;
	int		c_ea;
	int		c_f;
	int		c_c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**f;
	char	**c;
	int		height;
	int		width;
}	t_map;

typedef struct s_point
{
	float	y;
	float	x;
}	t_point;

typedef struct s_cast
{
	t_point	h;
	t_point	v;
	float	disth;
	float	distv;
	float	step_y;
	float	step_x;
	float	ray;
}	t_cast;

typedef struct s_var
{
	void		*mlx;
	void		*win;
	int			time;
	int			count;
	t_cast		*cast;
	t_img		*img;
	t_img		*img_g;
	t_player	*player;
	t_map		*map;

} t_var;

// window
int		setup_window(t_var *var);

// utils
void	ft_print_lst(t_map *map); /*a supp un jour*/
void	ft_print_tab(char **tab); /*a supp un jour*/
int		ft_check_space(char c);
float	radian(int degree);
char	**tab_cpy(char **tab, int size);


// parse
void 	ft_parse(int argc, char **argv, t_var *var);

// init free
t_map		*ft_init_map(void);
void		ft_free_all(t_var *var);
t_img		*init_img(void);
t_player	*init_player(t_var *var, int x, int y);

// check first part
int		ft_check_instruct(t_var *var);
char	*check_texture(t_map *map, int i, int *j);

// check map
int		check_map(t_var *var, int *i);
int		count_empty(char **tab);

// check map space
void		check_space_in_map(t_var *var, int i, int j);
int		delete_space(t_map *map);
void	add_space_end(t_map *map);
void	floodfill_space_wall(t_map *map, int x, int y, int c);

// check map wall
int		check_wall_min_max(t_var *var);
int		check_wall(t_map *map);

// mini_map
void	make_minimap(t_var *var);
void	draw_player(t_var *var, int color, int i, int y);
void	draw_dir(t_var *var, t_point cell, int color);
void	find_wall_ray(t_var *var, int type);
void	my_put_pixel(t_img *img, int y, int x, int color);
void	draw_minimap(t_var *var);

// raycasting
void	raycasting(t_var *var, int type);
int		check_raycasting(float new_y, float new_x, int type, t_var *var);
int		distance(t_point cell, float x0, float y0);
int		valid_point(t_var *var, t_point cell, int type);
// game
void	make_game(t_var *var);
void	wall_height(t_var *var, int dist, int i);
void	draw_game(t_img *img_g, int height, int width);

// cooridnates
int	ft_is_coordinates(t_var *var, t_map *map,int i, int *j);

// colors
// void	color_f(t_map *map, int i, int *j);
// void	color_c(t_map *map, int i, int *j);
int	ft_is_color(t_var *var, t_map *map, int i, int *j);



#endif