#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	ft_parse(argc, argv, &var);
	init_var(&var);
	setup_window(&var);
	ft_free_all(&var);
	return (0);
}
