#include "cub3D.h"

// // POUR TESTER - A SUPP QD PLUS BESOIN
// void	ft_print_lst(t_map *map)
// {
// 	t_list	*temp;

// 	temp = map->lst_map;
// 	while (temp)
// 	{
// 		printf("%s", (char *)temp->content);
// 		temp = temp->next;
// 	}
// }

// // POUR TESTER - A SUPP QD PLUS BESOIN
// void	ft_print_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("tab =%s$\n", tab[i]);
// 		i++;
// 	}
// }

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

int	modify_color(int color, double coeff)
{
	int	r;
	int	g;
	int	b;

	if (coeff < 0.0f) coeff = 0.0f;
	if (coeff > 1.0f) coeff = 1.0f;
	r = ((color >> 16) & 0xFF) * coeff;
	g = ((color >> 8) & 0xFF) * coeff;
	b = (color & 0xFF) * coeff;

	return ((r << 16) + (g << 8) + b);
}

int	check_in_map(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (0);
	if (x < 0 || x >= map->width)
		return (2);
	return (1);
}
