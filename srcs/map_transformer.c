/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transformer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 18:34:48 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_line *coords, int *z0, int *z1, t_draw *apply)
{
	if (apply->zoom < 1)
	{
		apply->zoom = 1;
		return ;
	}
	else if (apply->zoom > 30)
	{
		apply->zoom = 30;
		return ;
	}
	*z0 *= apply->zoom;
	*z1 *= apply->zoom;
	coords->x0 *= apply->zoom;
	coords->y0 *= apply->zoom;
	coords->x1 *= apply->zoom;
	coords->y1 *= apply->zoom;
}

int	translate(t_line *coords, t_draw *transform)
{
	coords->x0 += transform->translate_x;
	coords->y0 += transform->translate_y;
	coords->x1 += transform->translate_x;
	coords->y1 += transform->translate_y;
	return (0);
}

float	get_z_increment(int z, float factor)
{
	float	increment;

	increment = round(factor * sqrt(abs(z)));
	if (z > 0)
		return (-increment);
	return (increment);
}

void	rotate_x(double angle, int *x, int *y, int *z)
{
	int	tmp_y;
	int	tmp_z;

	if (!angle)
		return ;
	tmp_y = *y;
	tmp_z = *z;
	*x = *x;
	*y = round(tmp_y * cos(angle) + tmp_z * sin(angle));
	*z = round(tmp_y * cos(angle) - tmp_y * sin(angle));
}

void	isometric(int *x, int *y, int z)
{
	int	tmp;

	tmp = *x;
	*x = (tmp - *y) * cos(0.60);
	*y = (tmp + *y) * sin(0.60) - z / 10;
}
