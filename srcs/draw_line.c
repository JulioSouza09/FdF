/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:23:15 by joel              #+#    #+#             */
/*   Updated: 2025/08/12 18:15:42 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_pixel_put(int x, int y, t_data *data, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	handle_octants(t_math *vars, t_line *coords, int flag, int *delta)
{
	if (flag)
	{
		ft_swap(&coords->x0, &coords->x1);
		ft_swap(&coords->y0, &coords->y1);
	}
	vars->dx = coords->x1 - coords->x0;
	vars->dy = coords->y1 - coords->y0;
	if (*delta < 0)
		vars->dir = -1;
	else
		vars->dir = 1;
	*delta *= vars->dir;
}

static void	draw_line_h(t_line coords, t_data *data, int color)
{
	t_math	vars;
	int	i;

	handle_octants(&vars, &coords, coords.x0 > coords.x1, &vars.dy);
	i = 0;
	vars.p = 2 * vars.dy - vars.dx;
	while (i < vars.dx + 1)
	{
		ft_pixel_put(coords.x0 + i, coords.y0, data, color);
		if (vars.p >= 0)
		{
			coords.y0 += vars.dir;
			vars.p = vars.p - 2 * vars.dx;
		}
		vars.p = vars.p + 2 * vars.dy;
		++i;
	}
}

static void	draw_line_v(t_line coords, t_data *data, int color)
{
	t_math	vars;
	int	i;

	handle_octants(&vars, &coords, coords.y0 > coords.y1, &vars.dx);
	i = 0;
	vars.p = 2 * vars.dx - vars.dy;
	while (i < vars.dy + 1)
	{
		ft_pixel_put(coords.x0, coords.y0 + i, data, color);
		if (vars.p >= 0)
		{
			coords.x0 += vars.dir;
			vars.p = vars.p - 2 * vars.dy;
		}
		vars.p = vars.p + 2 * vars.dx;
		++i;
	}

}


void	draw_line(t_line coords, t_data *data, t_app *app)
{
	int	z0;
	int	z1;
	int	color0;
	int	color1;

	z0 = app->map->z[coords.y0][coords.x0].z;
	z1 = app->map->z[coords.y1][coords.x1].z;
	color0 = app->map->z[coords.y0][coords.x0].color;
	color1 = app->map->z[coords.y1][coords.x1].color;
	center_axis(&coords, app->map);
	zoom(&coords, &z0, &z1, &app->transform);
	if (app->transform.iso == TRUE)
	{
		isometric(&coords.x0, &coords.y0, z0);
		isometric(&coords.x1, &coords.y1, z1);
	}
	center(&coords);
	translate(&coords, &app->transform);
	if (abs(coords.x1 - coords.x0) > abs(coords.y1 - coords.y0))
		draw_line_h(coords, data, color0);
	else
		draw_line_v(coords, data, color1);
}
