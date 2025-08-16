/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:36:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 18:13:08 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_app	*init_app(char *filename)
{
	t_app	*app;
	t_map	*map;
	t_data	tmp;

	map = get_map(filename);
	if (!map)
		return (NULL);
	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		return (NULL);
	app->map = map;
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, filename);
	tmp.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_len, &tmp.end);
	app->img = tmp;
	app->transform.zoom = 1;
	app->transform.z = 1;
	app->transform.iso = TRUE;
	app->transform.angle = 0;
	return (app);
}

int	close_program(t_app *app)
{
	mlx_destroy_image(app->mlx, app->img.img);
	mlx_destroy_window(app->mlx, app->win);
	destroy_map(app->map);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	free(app);
	exit(0);
	return (0);
}
