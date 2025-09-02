/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:41:53 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/17 16:38:12 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	render(app);
	init_hooks(app);
	mlx_loop(app->mlx);
	close_program(app);
	return (0);
}

// draw_line tests
// t_line top = init_coords(200, 200, 1400, 200);
// t_line bottom = init_coords(200, 700, 1400, 700);
// t_line left = init_coords(200, 200, 200, 700);
// t_line right = init_coords(1400, 200, 1400, 700);
// draw_line(top, &app->img);
// draw_line(bottom, &app->img);
// draw_line(left, &app->img);
// draw_line(right, &app->img);
// mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
//
// map_creator tests
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
