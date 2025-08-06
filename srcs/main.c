/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:41:53 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/06 12:23:55 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
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
	t_map	*map = get_map(argv[1]);
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			ft_printf("%d", map->z[i][j].color);
			if (map->z[i][j + 1].z > 9)
				ft_printf(" ");
			else
				ft_printf("  ");
		}
		ft_printf("\n");
	}
	destroy_map(map);
	return (0);
}


//	/***** File handler *****/
//	int	output = 0;
//	int	i = 0;
//	/***** get_height() *****/
// 	output = get_height("maps/42.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	output = get_height("maps/japan.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	output = get_height("maps/france.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	output = get_height("maps/julia.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	/***** get_width() *****/
// 	output = get_width("maps/42.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	output = get_width("maps/japan.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	output = get_width("maps/france.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
//
//	output = get_width("maps/julia.fdf");
//	ft_printf("Test %d: %d\n", ++i, output);
