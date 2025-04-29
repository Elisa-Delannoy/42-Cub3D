#include "../cub3D.h"

void	ft_read_map(t_map *map, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&map->lst_map, ft_lstnew((line)));
		line = get_next_line(fd);
	}
	free(line);
}

char	**ft_map_into_tab(t_map	*map)
{
	int		i;
	t_list	*temp;

	i = 0;
	map->map = malloc((ft_lstsize(map->lst_map) + 1) * sizeof(char *));
	if (!map->map)
		return (NULL);
	temp = map->lst_map;
	while (temp)
	{
		map->map[i] = ft_strdup((char *)temp->content);
		temp = temp->next;
		i++;
	}
	map->map[i] = NULL;
	return (map->map);
}

int main(int argc, char **argv)
{
	t_map	map;
	(void)	argv;

	if (argc != 2)
		return (1);
	ft_init_map(&map);
	ft_read_map(&map, argv);
	ft_print_lst(&map);
	if (ft_map_into_tab(&map) == NULL)
		return (ft_free_all(&map), 1);
	ft_print_tab(&map);
	ft_free_all(&map);
	return (0);
}
