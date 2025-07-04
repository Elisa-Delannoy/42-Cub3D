/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:53:43 by edelanno          #+#    #+#             */
/*   Updated: 2025/06/24 14:03:06 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>

# define PI 3.14159265358979323846
# define MAP_SZ 20.0f
# define GAME_DURATION 120

typedef enum e_dir
{
	NORTH = 90,
	SOUTH = 270,
	EAST = 0,
	WEST = 180,
	MAP = 20,
	GAME = 64,
	DOOR = 'D',
	EXIT = 'X'
}	t_dir;

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
	int		c_d;
	int		c_x;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*door;
	char	*exit;
	int		color_f;
	int		color_c;
	int		height;
	int		width;
	int		nb_door;
	int		nb_exit;
}	t_map;

typedef struct s_light
{
	int		top;
	int		bottom;
	int		left_b;
	int		left_top;
	int		right_b;
	int		right_top;
	int		center;
	int		colo;
	double	coeff;
}	t_light;

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
	double	map_x;
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
	int		x0;
	int		y0;
	int		step_x;
	int		step_y;
	int		dist_x;
	int		dist_y;
	double	rel_x;
	double	rel_y;
	int		mini_x;
	int		mini_y;
	int		color;
}	t_minimap;

typedef struct s_var
{
	void			*win;
	void			*mlx;
	int				time;
	int				count;
	int				on_off;
	int				exit;
	int				a;
	long			start_t;
	double			height;
	double			width;
	int				end_g;
	struct timeval	tv;
	t_img			*img;
	t_img			*img_g;
	t_img			*torch;
	t_img			icon;
	t_img			*batterie;
	t_img			no_t;
	t_img			so_t;
	t_img			ea_t;
	t_img			we_t;
	t_img			door_t;
	t_img			exit_t;
	t_img			end;
	t_img			gameover;
	t_img			victory;
	t_cast			*cast;
	t_player		*player;
	t_map			*map;
	t_minimap		*minimap;
	t_light			*light;
}	t_var;


double		radian(int degree);
void		init_all_textures(t_var *var);
void		check_end_game(t_var *var, t_player *player);
void		movement(t_var *var, t_map *map, t_player *player);
void		ft_parse(int argc, char **argv, t_var *var);
void		init_var(t_var *var);
void		init_img_end(t_var *var);
void		check_space_in_map(t_var *var, int i, int j);
void		add_space_end(t_map *map);
void		floodfill_space_wall(t_map *map, int x, int y, int c);
void		make_minimap(t_var *var);
void		draw_dir(t_var *var, t_point cell, int color, int i);
void		my_put_pixel(t_img *img, int y, int x, int color);
void		draw_minimap(t_var *var);
void		check_minimap_texture(t_var *var, int cell_x, int cell_y);
void		draw_mini_wall(t_var *var, int start_x, int start_y, t_img img);
void		move_up(t_map *map, t_player *player, double vitesse);
void		move_down(t_map *map, t_player *player, double vitesse);
void		move_left(t_map *map, t_player *player, double vitesse);
void		move_right(t_map *map, t_player *player, double vitesse);
void		rotate(t_player *player, double angle);
void		raycasting(t_var *var, t_cast *cast);
void		find_wall_dir(t_cast *cast);
void		find_pos_texture(t_var *var, t_cast *cast);
void		draw_img_in_img(t_var *var, t_img image, int start_x, int start_y);
void		make_game(t_var *var);
void		draw_game(t_var *var, t_img *img_g, t_light *light);
void		draw_wall(t_var *var, t_cast *cast, int i);
void		door(t_var *var, t_map *map, int i, int *j);
void		open_close_d(t_var *var, t_map *map);
void		clear_all(t_var *var);
char		*check_texture(t_map *map, int i, int *j);
char		**tab_cpy(char **tab, int size);
int			check_outside_wall(t_map *map);
int			ft_check_space(char c);
int			check_wall(t_map *map);
int			ft_free_all(t_var *var);
int			delete_space(t_map *map);
int			ft_is_coordinates(t_var *var, t_map *map, int i, int *j);
int			ft_is_color(t_var *var, t_map *map, int i, int *j);
int			ft_is_door(t_var *var, t_map *map, int i, int *j);
int			ft_is_exit(t_var *var, t_map *map, int i, int *j);
int			check_w_s_d(t_map *map, int i, int j);
int			setup_window(t_var *var);
int			mouse_movement(int x, int y, t_var *var);
int			active_mouse(int button, int x, int y, t_var *var);
int			key_release(int keycode, t_var *var);
int			key_press(int keycode, t_var *var);
int			select_key(int keycode, t_var *var, int value);
int			rgb_to_int(char **tab);
int			shadow(int color, double coeff);
int			check_in_map(t_map *map, int y, int x);
int			check_time(t_var *var);
int			check_map(t_var *var, int *i);
int			count_character(char **tab, char c);
int			ft_check_instruct(t_var *var);
t_img		*init_torch(t_var *var);
t_light		*init_light(t_var *var);
t_img		*init_img(void);
t_player	*init_player(t_var *var, int x, int y);
t_minimap	*init_minimap(void);
t_cast		*init_cast(void);
t_img		*set_timer(t_var *var);
t_map		*ft_init_map(void);

#endif