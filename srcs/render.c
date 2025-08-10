/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:00:22 by joel              #+#    #+#             */
/*   Updated: 2025/08/10 13:54:16 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw(int x, int y, t_data *img)
{
	t_line	coords;

	if (x > 0)
	{
		coords = init_coords((x-1) * 70, y * 70, x * 70, y * 70);
		draw_line(coords, img);
	}
	if (y > 0)
	{
		coords = init_coords(x * 70, (y-1) * 70, x * 70, y * 70);
		draw_line(coords, img);
	}
}

void	render(t_app *app)
{
	int		i;
	int		j;

	i = 0;
	while (i < app->map->height)
	{
		j = 0;
		while (j < app->map->width)
		{
			draw(j, i, &app->img);
			++j;
		}
		++i;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
}
