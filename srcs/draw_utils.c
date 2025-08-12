/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:30:00 by joel              #+#    #+#             */
/*   Updated: 2025/08/12 18:15:22 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line init_coords(int x0, int y0, int x1, int y1)
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

void	zoom(t_line *coords, int *z0, int *z1, t_draw *apply)
{
	*z0 *= apply->zoom;
	*z1 *= apply->zoom;
	coords->x0 *= apply->zoom;
	coords->y0 *= apply->zoom;
	coords->x1 *= apply->zoom;
	coords->y1 *= apply->zoom;
}

void	center(t_line *coords)
{
	coords->x0 += WIN_WIDTH / 2;
	coords->y0 += WIN_HEIGHT / 2;
	coords->x1 += WIN_WIDTH / 2;
	coords->y1 += WIN_HEIGHT / 2;
}

int	translate(t_line *coords, t_draw *transform)
{
	coords->x0 += transform->translate_x;
	coords->y0 += transform->translate_y;
	coords->x1 += transform->translate_x;
	coords->y1 += transform->translate_y;
	return (0);
}
