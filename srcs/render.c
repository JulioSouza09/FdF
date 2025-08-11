/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:00:22 by joel              #+#    #+#             */
/*   Updated: 2025/08/10 20:49:04 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
	int	tmp;

	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - z;
}

void	render(t_app *app)
{
	int		i;
	int		j;
	t_line	coords;

	i = 0;
	while (i < app->map->height)
	{
		j = 0;
		while (j < app->map->width)
		{
			if (j > 0)
			{
				coords = init_coords((j-1), i, j, i);
				draw_line(coords, &app->img, app->map, &app->transform);
			}
			if (i > 0)
			{
				coords = init_coords(j, (i-1), j, i);
				draw_line(coords, &app->img, app->map, &app->transform);
			}
			++j;
		}
		++i;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
}
