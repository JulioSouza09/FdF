/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:42:21 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/12 18:16:01 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define KeyPress 2
#define KeyPressMask 1L<<0
#define DestroyNotify 17
#define ESC 65307
#define MINUS 65453
#define PLUS 65451
#define O 111
#define I 105
#define ArrowUp 65362
#define ArrowDown 65364
#define ArrowLeft 65361
#define ArrowRight 65363
#define TRANSLATE_STEP 10


int	handle_keypress(int keycode, t_app *app)
{
	//ft_printf("%d\n", keycode);
	if (keycode == ESC)
		close_program(app);
	if (keycode == MINUS)
		app->transform.zoom -= 1;
	else if (keycode == PLUS)	
			app->transform.zoom += 1;
	else if (keycode == ArrowUp)
		app->transform.translate_y -= TRANSLATE_STEP;
	else if (keycode == ArrowDown)
		app->transform.translate_y += TRANSLATE_STEP;
	else if (keycode == ArrowLeft)
		app->transform.translate_x -= TRANSLATE_STEP;
	else if (keycode == ArrowRight)
		app->transform.translate_x += TRANSLATE_STEP;
	else if (keycode == O)
		app->transform.iso = FALSE;
	else if (keycode == I)
		app->transform.iso = TRUE;
	return (0);
}

void	init_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx, render, app);
	mlx_hook(app->win, KeyPress, KeyPressMask, handle_keypress, app);
	mlx_hook(app->win, DestroyNotify, 0, close_program, app);
}
