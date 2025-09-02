/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:30:00 by joel              #+#    #+#             */
/*   Updated: 2025/08/16 18:11:58 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_line	init_coords(int x0, int y0, int x1, int y1)
{
	t_line	coords;

	coords.x0 = x0;
	coords.y0 = y0;
	coords.x1 = x1;
	coords.y1 = y1;
	return (coords);
}

void	center_axis(t_line *coords, t_map *map)
{
	coords->x0 -= map->width / 2;
	coords->y0 -= map->height / 2;
	coords->x1 -= map->width / 2;
	coords->y1 -= map->height / 2;
}

void	center(t_line *coords)
{
	coords->x0 += WIN_WIDTH / 2;
	coords->y0 += WIN_HEIGHT / 2;
	coords->x1 += WIN_WIDTH / 2;
	coords->y1 += WIN_HEIGHT / 2;
}

double	degrees_to_rad(double degree)
{
	return (degree * (M_PI / 180));
}
