/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 15:27:05 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init(t_vars *vars, char *filename)
{
	t_dimension	dims;

	vars->grid = get_map(filename, &dims);
	if (!vars->grid)
	{
		close_win(vars);
		return (1);
	}
	vars->init = mlx_init();
	vars->win = mlx_new_window(vars->init, WIN_WIDTH, WIN_HEIGHT, filename); 
	vars->img.img = mlx_new_image(vars->init, WIN_WIDTH, WIN_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_len, &vars->img.end);
	vars->width = dims.width;
	vars->height = dims.height;
	vars->offset = OFFSET;
	vars->translate.x = 0;
	vars->translate.y = 0;
	vars->translate.z = 0;
	vars->degree = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	if (!valid_suffix(argv[1]))
	{
		ft_putendl_fd("fdf: invalid filetype", 2);
		return (2);
	}
	if (init(&vars, argv[1]))
		return (3);
	mlx_loop_hook(vars.win, handle_no_event, &vars);
	mlx_hook(vars.win, 2, 	1L<<0, handle_keypress, &vars);
	mlx_hook(vars.win, 4, 1L<<2, handle_buttonpress, &vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_loop(vars.init);
	return (0);
}
