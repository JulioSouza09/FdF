/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:27:35 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 18:48:42 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom(int keycode, t_app *app)
{
	if (keycode == MINUS)
		app->transform.zoom -= ZOOM_FACTOR;
	else if (keycode == PLUS)
		app->transform.zoom += ZOOM_FACTOR;
}

void	handle_translation(int keycode, t_app *app)
{
	if (keycode == ARROWUP)
		app->transform.translate_y -= TRANSLATE_STEP;
	else if (keycode == ARROWDOWN)
		app->transform.translate_y += TRANSLATE_STEP;
	else if (keycode == ARROWLEFT)
		app->transform.translate_x -= TRANSLATE_STEP;
	else if (keycode == ARROWRIGHT)
		app->transform.translate_x += TRANSLATE_STEP;
}

void	handle_projection(int keycode, t_app *app)
{
	if (keycode == O)
		app->transform.iso = FALSE;
	else if (keycode == I)
		app->transform.iso = TRUE;
}

void	handle_z(int keycode, t_app *app)
{
	if (keycode == Z)
		app->transform.z -= Z_FACTOR;
	else if (keycode == X)
		app->transform.z += Z_FACTOR;
}

void	handle_rotation(int keycode, t_app *app)
{
	if (keycode == A)
		app->transform.angle -= ROTATION_FACTOR;
	else if (keycode == D)
		app->transform.angle += ROTATION_FACTOR;
}
