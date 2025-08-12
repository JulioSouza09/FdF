/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:00:22 by joel              #+#    #+#             */
/*   Updated: 2025/08/12 17:04:20 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
	int	tmp;

	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - z / 15;
}

int	render(t_app *app)
{
	int		i;
	int		j;
	t_line	coords;

	i = -1;
	ft_memset(app->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * 4);
	while (++i < app->map->height)
	{
		j = -1;
		while (++j < app->map->width)
		{
			if (j > 0)
			{
				coords = init_coords((j-1), i, j, i);
				draw_line(coords, &app->img, app);
			}
			if (i > 0)
			{
				coords = init_coords(j, (i-1), j, i);
				draw_line(coords, &app->img, app);
			}
		}
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	return (0);
}
