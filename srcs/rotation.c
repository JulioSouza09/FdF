/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:31:39 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 13:31:47 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	degrees_to_radians(double degree)
{
	return (degree * (M_PI / 180));
}

t_coord	rotate_point(double degree, int x, int y, int z)
{
	t_coord result;
	double dg;

	dg = degrees_to_radians(degree);
	result.x = x + WIN_WIDTH / 2;
	result.y = y * cos(dg) + z * sin(dg) + WIN_HEIGHT / 2;
	result.z = z * cos(dg) - y * sin(dg);
	return (result);
}

void	rotate_matrix(t_point **map, int degree, int width, int height, t_data *img, int offset)
{
	int		i;
	int		j;
	t_coord	point;

	i = 0;
	(void) offset;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			point = rotate_point(degree, map[i][j].x, map[i][j].y, map[i][j].z);
			map[i][j].x2 = point.x;
			map[i][j].y2 = point.y - point.z;
			if (j >= 1)
				draw_line(map[i][j - 1].x2, map[i][j - 1].y2, map[i][j].x2, map[i][j].y2, img, map[i][j].color);
			if (i >= 1)
				draw_line(map[i - 1][j].x2, map[i - 1][j].y2, map[i][j].x2, map[i][j].y2, img, map[i][j].color);
			++j;
		}
		++i;
	}
}
