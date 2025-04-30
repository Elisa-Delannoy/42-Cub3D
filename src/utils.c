
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
void	ft_print_tab(t_map *map)
{
	int	i;

	i = 0;
	while (map->tab_map[i])
	{
		printf("%s$\n", map->tab_map[i]);
		i++;
	}
}
