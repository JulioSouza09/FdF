/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:42:21 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 18:30:04 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keycode, t_app *app)
{
	if (keycode == ESC)
		close_program(app);
	handle_zoom(keycode, app);
	handle_translation(keycode, app);
	handle_projection(keycode, app);
	handle_z(keycode, app);
	handle_rotation(keycode, app);
	return (0);
}

void	init_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx, render, app);
	mlx_hook(app->win, KEYPRESS, 1L << 0, handle_keypress, app);
	mlx_hook(app->win, DESTROYNOTIFY, 0, close_program, app);
}
