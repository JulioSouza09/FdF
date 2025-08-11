/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:42:21 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/11 17:42:25 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define KeyPress 2
#define KeyPressMask 1L<<0
#define DestroyNotify 17
#define ESC 65307
#define MINUS 65453
#define PLUS 65451

int	handle_keypress(int keycode, t_app *app)
{
//	ft_printf("%d\n", keycode);
	if (keycode == ESC)
		close_program(app);
	if (keycode == MINUS || keycode == PLUS)
	{
		mlx_clear_window(app->mlx, app->win);
		ft_memset(app->img.addr, 0, WIN_WIDTH * WIN_HEIGHT * 4);
		if (keycode == MINUS)
			app->transform.zoom--;
		else
			app->transform.zoom++;
	}
	return (0);
}

void	init_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx, render, app);
	mlx_hook(app->win, KeyPress, KeyPressMask, handle_keypress, app);
	mlx_hook(app->win, DestroyNotify, 0, close_program, app);
}
