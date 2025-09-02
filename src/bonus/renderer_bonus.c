/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:00:22 by joel              #+#    #+#             */
/*   Updated: 2025/08/16 18:38:57 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
				coords = init_coords((j - 1), i, j, i);
				draw_line(coords, &app->img, app);
			}
			if (i > 0)
			{
				coords = init_coords(j, (i - 1), j, i);
				draw_line(coords, &app->img, app);
			}
		}
	}
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	return (0);
}
