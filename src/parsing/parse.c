#include "cub3D.h"

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
	map->tab_file = malloc((ft_lstsize(map->lst_map) + 1) * sizeof(char *));
	if (!map->tab_file)
		return (NULL);
	temp = map->lst_map;
	while (temp)
	{
		map->tab_file[i] = ft_strdup((char *)temp->content);
		temp = temp->next;
		i++;
	}
	map->tab_file[i] = NULL;
	return (map->tab_file);
}

int	check_name(char **argv)
{
	char	*name;

	name = ft_strrchr(argv[1], '.');
	if (name == NULL)
		return (ft_putstr_fd("map's name must end with .cub\n", 2), 1);
	if (ft_strncmp(".cub", name, 4) != 0 || ft_strlen(name) != 4)
		return (ft_putstr_fd("map's name must end with .cub\n", 2), 1);
	return (0);
}

void	ft_parse(int argc, char **argv, t_var *var)
{
	t_map	*map;

	if (argc != 2 || check_name(argv) == 1)
		return (exit(1));
	map = ft_init_map();
	if (ft_read_map(map, argv) == 1)
		return (free(map), exit(1));
	if (ft_map_into_tab(map) == NULL)
		return (ft_free_all(var), exit(1));
	var->map = map;
	if (ft_check_instruct(var) != 0)
		return (ft_free_all(var), exit(1));
}
