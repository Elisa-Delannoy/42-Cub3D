#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

typedef struct s_player
{
	int x;
	int y;

} t_player;

typedef struct s_var
{
	void	*mlx;
	void	*win; 
} t_var;



typedef struct s_map
{
	t_list	*lst_map;
	char	**map;
}	t_map;



// utils
void	ft_print_lst(t_map *map); /*a supp un jour*/
void	ft_print_tab(t_map *map); /*a supp un jour*/



// init free
void	ft_init_map(t_map *map);
void	ft_free_all(t_map *map);

#endif