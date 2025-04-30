#include "../cub3D.h"

int main(int argc, char **argv)
{
	t_var	var; 

	var.map = ft_parse(argc, argv);
	// setup_window(&var);
	ft_free_all(var.map);
	return (0);
}