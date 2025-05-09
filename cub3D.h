#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

# define PI 3.14159265358979323846

typedef enum e_dir
{
	NORTH = 0,
	SOUTH = 180,
	EAST = 90,
	WEAST = 270,
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
}				t_key;

typedef struct s_cast
{
	
}	t_cast;

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
	int 	bits_per_pixel;
	int 	size_line;
	int		endian;
}	t_img;

typedef struct s_map
{
	t_list	*lst_map;
	char	**tab_file;
	char	**tab_map;
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
	char 	**c;
	int		height;
	int		width;
	// int		i_begin_map;

}	t_map;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	int		time;
	int		count;
	t_img		*img;
	t_player	*player;
	t_map		*map;

} t_var;

// window
int		setup_window(t_var *var);

// utils
void	ft_print_lst(t_map *map); /*a supp un jour*/
void	ft_print_tab(char **tab); /*a supp un jour*/
int		ft_check_space(char c);


// parse
void 	ft_parse(int argc, char **argv, t_var *var);

// init free
t_map	*ft_init_map(void);
void	ft_free_all(t_map *map);
t_img	*init_img(void);

// check first part
int		ft_check_instruct(t_var *var);
int		ft_is_coordinates(t_map *map,int i, int *j);
char	*check_texture(t_map *map, int i, int *j);

// check map
void	check_map(t_var *var, int *i);
float	radian(int degree);

// mini_map
void	make_minimap(t_var *var);
void	draw_player(t_var *var, int color, int i, int y);
void	draw_dir(t_var *var, int x1, int y1, int color);
void	find_wall_ray(t_var *var, int type);

// cooridnates
int	ft_is_coordinates(t_map *map,int i, int *j);

// colors
// void	color_f(t_map *map, int i, int *j);
// void	color_c(t_map *map, int i, int *j);
int	ft_is_color(t_map *map, int i, int *j);


#endif