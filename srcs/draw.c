/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:40:57 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 15:35:34 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	dst = data->addr + (y * data->line_len) + (x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(int x_start, int y_start, int x_end, int y_end, t_data *img_data, int color)
{
	float	delta_x;
	float	delta_y;
	float	y;
	int		pixel;
	int		tmp;

	if (x_end < x_start)
	{
		tmp = x_start;
		x_start = x_end;
		x_end = tmp;
		tmp = y_start;
		y_start = y_end;
		y_end = tmp;
	}
	delta_x = x_end - x_start;
	delta_y = y_end - y_start;
	pixel = x_start;
	while (pixel > x_end)
	{
		y = (delta_y / delta_x) * (pixel - x_start) + y_start;
		ft_pixel_put(img_data, pixel, y, color);
		--pixel;
	}
	while (pixel < x_end)
	{
		y = (delta_y / delta_x) * (pixel - x_start) + y_start;
		ft_pixel_put(img_data, pixel, y, color);
		++pixel;
	}
}

static void	init_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

void	init_grid(t_point **array, int width, int height, float offset, t_data *test, t_point translate)
{
	int		i;
	int		j;
	t_point	start;
	t_point	position;
	t_point	tmp;

	position.x = width / 2;
	position.y = height / 2;
	tmp.x = 0 + (position.y - position.x) * (offset * 2);
	tmp.y = 0 - (position.x + position.x) * offset;
	i = 0;
	init_point(&start, tmp.x, tmp.y);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			init_point(&array[i][j], start.x + translate.x, start.y + translate.y);
			if (array[i][j].z != 0)
				array[i][j].z += translate.z;
			array[i][j].y -= round((array[i][j].z) * (offset / 7));
			start.x += offset * 2;
			start.y += offset;
			if (j >= 1)
				draw_line(array[i][j - 1].x, array[i][j - 1].y, array[i][j].x, array[i][j].y, test, array[i][j].color);
			if (i >= 1)
				draw_line(array[i - 1][j].x, array[i - 1][j].y, array[i][j].x, array[i][j].y, test, array[i][j].color);
			++j;
		}
		++i;
		start.x = tmp.x - (((offset*2) * i));
		start.y = tmp.y + ((offset * i));
	}
}
