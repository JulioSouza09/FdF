/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 13:32:56 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_hex(char *nbr)
{
	int	i;
	int	result;

	i = 0;
	if (!ft_strncmp("0x", nbr, 2))
		i += 2;
	result = 0;
	while (nbr[i])
	{
		result *= 16;
		if (nbr[i] >= 'a' && nbr[i] <= 'f')
			result += nbr[i] - 'a';
		else if (nbr[i] >= 'A' && nbr[i] <= 'F')
			result += nbr[i] - 'A';
		else if (nbr[i] >= '0' && nbr[i] <= '9')
			result += nbr[i] - '0';
		++i;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	void	*init;
	void	*win;
	t_data	img;
	t_point	**grid;
	t_dimension	dimensions;
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
	grid = get_map(argv[1], &dimensions);
	init = mlx_init();
	win = mlx_new_window(init, WIN_WIDTH, WIN_HEIGHT, "Test");
	img.img = mlx_new_image(init, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.end);
	vars.init = init;
	vars.win = win;
	vars.grid = grid;
	vars.width = dimensions.width;
	vars.height = dimensions.height;
	vars.offset = OFFSET;
	vars.img = img;
	vars.translate.x = 0;
	vars.translate.y = 0;
	vars.translate.z = 0;
	vars.degree = 1;
	printf("%f\n", degrees_to_radians(265));
	init_grid(grid, dimensions.width, dimensions.height, OFFSET, &img, vars.translate);
	mlx_put_image_to_window(init, win, img.img, 0, 0);
	mlx_loop_hook(vars.win, handle_no_event, &vars);
	mlx_hook(vars.win, 2, 	1L<<0, handle_keypress, &vars);
	mlx_hook(vars.win, 4, 1L<<2, handle_buttonpress, &vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_loop(init);
	return (0);
}
