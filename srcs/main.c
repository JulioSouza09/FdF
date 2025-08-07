/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:41:53 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/07 13:05:04 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_app	*app;

	if (argc != 2)
	{
		usage_error(argv[0]);
		return (1);
	}
	if (!valid_suffix(argv[1]))
	{
		ft_putendl_fd("FdF: Invalid filetype. Expected '.fdf' file.", 2);
		return (2);
	}
	app = init_app(argv[1]);
	if (!app)
	{
		ft_putendl_fd("FdF: Initialization error!", 2);
		return (4);
	}
	mlx_loop(app->mlx);
	close_program(app);
	return (0);
}

	//char	files[4][100] = {
	//	"maps/julia.fdf",
	//	"maps/japan.fdf",
	//	"maps/42.fdf",
	//	"maps/france.fdf"
	//};
	//for (int x = 0; x < 4; x++)
	//{
	//	ft_printf("Map: %s\n", files[x]);
	//	t_map	*map = get_map(files[x]);
	//	
	//	ft_printf("Map Height: %d\n", map->height);
	//	ft_printf("Map Width: %d\n\n", map->width);
	//	destroy_map(map);
	//}
	// t_map	*map = get_map(argv[1]);
	// for (int i = 0; i < map->height; i++)
	// {
	// 	for (int j = 0; j < map->width; j++)
	// 	{
	// 		ft_printf("%d", map->z[i][j].z);
	// 		if (j < map->width - 1 && map->z[i][j + 1].z > 9)
	// 			ft_printf(" ");
	// 		else
	// 			ft_printf("  ");
	// 	}
	// 	ft_printf("\n");
	// }
	// destroy_map(map);

