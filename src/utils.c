
# include "../cub3D.h"

// POUR TESTER - A SUPP QD PLUS BESOIN
void	ft_print_lst(t_map *map)
{
	t_list	*temp;

	temp = map->lst_map;
	while (temp)
	{
		printf("%s", (char *)temp->content);
		temp = temp->next;
	}
}

// POUR TESTER - A SUPP QD PLUS BESOIN
void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s$\n", tab[i]);
		i++;
	}
}

int	ft_check_space(t_map *map, int i, int j)
{
	if (map->tab_file[i][j] == ' ')
		return (0);
	return (1);
}
