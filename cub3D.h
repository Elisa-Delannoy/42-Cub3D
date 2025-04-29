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

#endif