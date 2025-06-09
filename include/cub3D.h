#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define PI 3.14159265358979323846
# define GAME_sz 1.0f
# define MAP_sz 20.0f

typedef enum e_dir
{
	NORTH = 90,
	SOUTH = 270,
	EAST = 0,
	WEST = 180,
	MAP = 20,
	GAME = 64,
	DOOR = 'D' /*bonus*/
}	t_dir;

typedef enum e_key
{
	RIGHT = 100,
	LEFT = 97,
	UP = 119,
	DOWN = 115,
	TURN_L = 65361,
	TURN_R = 65363,
	ESC = 65307,
	SPRINT = 65505,
	MOUSE = 65288,
	OPEN_CLOSE = 101, /*bonus*/
	SPACE = 32
}	t_key;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		m_up;
	int		m_down;
	int		m_left;
	int		m_right;
	int		mouse;
	double	speed;
	double	sprint;
	int		t_left;
	int		t_right;
	int		o_c_door;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*data_img;
	int		endian;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
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
	int		c_d; /*bonus*/
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*door; /*bonus*/
	int		color_f;
	int		color_c;
	int		height;
	int		width;
}	t_map;

typedef struct s_point
{
	double	y;
	double	x;
}	t_point;

typedef struct s_cast
{
	t_point	hit;
	t_img	texture;
	double	dist;
	int		wall_h;
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
	int		wall_dir;
	double 	map_x;
	double	map_y;
	double	dist_x;
	double	dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	int		text_pos_x;
	double	double_text_pos_y;
	int		text_pos_y;
	int		coordinates;

}	t_cast;


typedef struct s_minimap
{
	int	x0;
	int	y0;
	int	step_x;
	int	step_y;
	int	dist_x;
	int	dist_y;
}	t_minimap;

typedef struct s_var
{
	void		*mlx;
	void		*win;
	int			time;
	int			count;
	int			on_off;
	int			a;
	double		height;
	double		width;
	t_cast		*cast;
	t_img		*img;
	t_img		*img_g;
	t_img		*torch;
	t_player	*player;
	t_map		*map;
	t_img		no_t;
	t_img		so_t;
	t_img		ea_t;
	t_img		we_t;
	t_img		door_t; /*bonus*/
	t_minimap	*minimap;
} t_var;

// window
int		setup_window(t_var *var);
void	init_all_textures(t_var *var);

// utils
void	ft_print_lst(t_map *map); /*a supp un jour*/
void	ft_print_tab(char **tab); /*a supp un jour*/
int		ft_check_space(char c);
double	radian(int degree);
char	**tab_cpy(char **tab, int size);
int		rgb_to_int(char **tab);
int		modify_color(int color, double coeff);
int		check_in_map(t_map *map, int y, int x);
// parse
void 	ft_parse(int argc, char **argv, t_var *var);

// init free
t_map		*ft_init_map(void);
void		ft_free_all(t_var *var);
t_img		*init_img(void);
t_player	*init_player(t_var *var, int x, int y);
t_minimap	*init_minimap(void);

// check first part
int		ft_check_instruct(t_var *var);
char	*check_texture(t_map *map, int i, int *j);

// check map
int		check_map(t_var *var, int *i);
int		count_empty(char **tab);

// check map space
void	check_space_in_map(t_var *var, int i, int j);
int		delete_space(t_map *map);
void	add_space_end(t_map *map);
void	floodfill_space_wall(t_map *map, int x, int y, int c);

// check map wall
int		check_wall_min_max(t_var *var);
int		check_wall(t_map *map);
void	empty_for_window(t_map *map);

// mini_map
void	make_minimap(t_var *var);
void	draw_player(t_var *var, int color, int i, int y);
void	draw_dir(t_var *var, t_point cell, int color, int i);
void	my_put_pixel(t_img *img, int y, int x, int color);
void	draw_minimap(t_var *var);

//movement
void	move_up(t_map *map, t_player *player, double vitesse);
void	move_down(t_map *map, t_player *player, double vitesse);
void	move_left(t_map *map, t_player *player, double vitesse);
void	move_right(t_map *map, t_player *player, double vitesse);
void	rotate(t_player *player, double angle);

// raycasting
void	raycasting(t_var *var, t_cast *cast);

//torch
void	draw_torch(t_var *var, int i);
t_img	*init_torch(t_var *var);


// game
void	make_game(t_var *var);
void	draw_game(t_img *img_g, t_var *var);
void	draw_wall(t_var *var, t_cast *cast, int i);

// cooridnates
int	ft_is_coordinates(t_var *var, t_map *map,int i, int *j);

// colors
int	ft_is_color(t_var *var, t_map *map, int i, int *j);

// bonus
void	door(t_var *var, t_map *map, int i, int *j);
int		ft_is_door(t_var *var, t_map *map, int i, int *j);

void	open_close_d(t_var *var, t_map *map, int speed);

#endif