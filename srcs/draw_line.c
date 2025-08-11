/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joel <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:23:15 by joel              #+#    #+#             */
/*   Updated: 2025/08/10 20:42:59 by jcesar-s         ###   ########.fr       */
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

static void	draw_line_h(t_line coords, t_data *data)
{
	t_math	vars;
	int	i;

	handle_octants(&vars, &coords, coords.x0 > coords.x1, &vars.dy);
	i = 0;
	vars.p = 2 * vars.dy - vars.dx;
	while (i < vars.dx + 1)
	{
		ft_pixel_put(coords.x0 + i, coords.y0, data, 0xFFFFFF);
		if (vars.p >= 0)
		{
			coords.y0 += vars.dir;
			vars.p = vars.p - 2 * vars.dx;
		}
		vars.p = vars.p + 2 * vars.dy;
		++i;
	}
}

static void	draw_line_v(t_line coords, t_data *data)
{
	t_math	vars;
	int	i;

	handle_octants(&vars, &coords, coords.y0 > coords.y1, &vars.dx);
	i = 0;
	vars.p = 2 * vars.dx - vars.dy;
	while (i < vars.dy + 1)
	{
		ft_pixel_put(coords.x0, coords.y0 + i, data, 0xFFFFFF);
		if (vars.p >= 0)
		{
			coords.x0 += vars.dir;
			vars.p = vars.p - 2 * vars.dy;
		}
		vars.p = vars.p + 2 * vars.dx;
		++i;
	}

}

void	draw_line(t_line coords, t_data *data, t_map *map, t_draw *apply)
{
	int	z0;
	int	z1;

	z0 = map->z[coords.y0][coords.x0].z;
	z1 = map->z[coords.y1][coords.x1].z;
	coords.x0 -= map->width / 2;
	coords.y0 -= map->height / 2;
	coords.x1 -= map->width / 2;
	coords.y1 -= map->height / 2;
	coords.x0 *= apply->zoom;
	coords.y0 *= apply->zoom;
	coords.x1 *= apply->zoom;
	coords.y1 *= apply->zoom;
	isometric(&coords.x0, &coords.y0, z0);
	isometric(&coords.x1, &coords.y1, z1);
	coords.x0 += WIN_WIDTH / 2;
	coords.y0 += WIN_HEIGHT / 2;
	coords.x1 += WIN_WIDTH / 2;
	coords.y1 += WIN_HEIGHT / 2;
	if (abs(coords.x1 - coords.x0) > abs(coords.y1 - coords.y0))
		draw_line_h(coords, data);
	else
		draw_line_v(coords, data);
}
