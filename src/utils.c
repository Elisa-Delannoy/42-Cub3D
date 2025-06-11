#include "cub3D.h"

int	ft_check_space(char c)
{
	if (c == ' ')
		return (0);
	return (1);
}

double	radian(int degree)
{
	return (degree * PI / 180);
}

char	**tab_cpy(char **tab, int size)
{
	int		i;
	char	**new_tab;

	i = 0;
	new_tab = malloc((size + 1) * sizeof(char *));
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	rgb_to_int(char **tab)
{
	return ((ft_atoi(tab[0]) << 16) + (ft_atoi(tab[1]) << 8) + ft_atoi(tab[2]));
}

int	shadow(int color, double coeff)
{
	int	r;
	int	g;
	int	b;

	if (coeff < 0.0f)
		coeff = 0.0f;
	if (coeff > 1.0f)
		coeff = 1.0f;
	r = ((color >> 16) & 0xFF) * coeff;
	g = ((color >> 8) & 0xFF) * coeff;
	b = (color & 0xFF) * coeff;
	return ((r << 16) + (g << 8) + b);
}
