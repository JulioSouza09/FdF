/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:36:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/07 13:01:45 by jcesar-s         ###   ########.fr       */
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
	app = malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	app->map = map;
	app->mlx = mlx_init();
	app->win= mlx_new_window(app->mlx, 1600, 900, filename);
	tmp.img = mlx_new_image(app->mlx, 1600, 900);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_len, &tmp.end);
	app->img = tmp;
	return (app);
}

void	close_program(t_app *program)
{
	mlx_destroy_image(program->mlx, program->img.img);
	mlx_destroy_window(program->mlx, program->win);
	destroy_map(program->map);
	free(program->mlx);
	free(program->img.addr);
	free(program);
}
