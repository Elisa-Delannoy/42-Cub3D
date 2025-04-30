#include "../cub3D.h"

int	ft_read_map(t_map *map, char **argv)
{
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_lstadd_back(&map->lst_map, ft_lstnew((line)));
		line = get_next_line(fd);
	}
	free(line);
	return (0);
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

int ft_parse(t_map *map, int argc, char **argv)
{
	if (argc != 2)
		return (1);
	ft_init_map(map);
	if (ft_read_map(map, argv) == 1)
		return (1);
	// ft_print_lst(map);
	if (ft_map_into_tab(map) == NULL)
		return (ft_free_all(map), 1);
	ft_print_tab(map);
	printf ("check instruc = %d", ft_check_instruct(map));
	ft_free_all(map);
	return (0);
}



