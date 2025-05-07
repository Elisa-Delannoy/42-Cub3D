#include "../cub3D.h"

int main(int argc, char **argv)
{
	t_var	var; 

	ft_parse(argc, argv, &var);
	var.time = 3000;
	var.count = 0;
	// setup_window(&var);
	ft_free_all(var.map);
	return (0);
}
