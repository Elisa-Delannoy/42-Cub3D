#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

typedef struct s_player
{
	int		 x;
	int		 y;
	double dir;
} t_player;


typedef struct s_map
{
	t_list	*lst_map;
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
	char	*f;
	char 	*c;
	int		height;
	int		i_begin_map;

}	t_map;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	t_player	*player;
	t_map		*map;

} t_var;

// window
int		setup_window(t_var *var);

// utils
void	ft_print_lst(t_map *map); /*a supp un jour*/
void	ft_print_tab(t_map *map); /*a supp un jour*/


// parse
t_map 	*ft_parse(int argc, char **argv);

// init free
t_map	*ft_init_map(void);
void	ft_free_all(t_map *map);


// check first part
int		ft_check_instruct(t_map *map);
void	ft_check_ascii(t_map *map, int *i);


// mini_map
void	make_minimap(t_var *var);

#endif