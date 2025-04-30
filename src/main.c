#include "../cub3D.h"

int main(int argc, char **argv)
{
	t_var	var; 

	ft_parse(var.map, argc, argv);
	setup_window(&var);
	return (0);
}