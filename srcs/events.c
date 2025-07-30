/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:29:11 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 13:29:13 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_no_event(void *data)
{
	if (!data)
		return (0);
	return (0);
}

int	handle_buttonpress(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 4 || (button == 5 && vars->offset >= 2))
	{
		mlx_clear_window(vars->init, vars->win);
		ft_memset(vars->img.addr, 0, WIN_HEIGHT * WIN_WIDTH * 4);
		if (button == 4)
			vars->offset += 1;
		if (button == 5)
			vars->offset -= 1;
		init_grid(vars->grid, vars->width, vars->height, vars->offset, &vars->img, vars->translate);
		mlx_put_image_to_window(vars->init, vars->win, vars->img.img, 0, 0);
	}
	if (!vars)
		return (0);
	return (0);
}

int	close_win(t_vars *vars)
{
	destroy_map(vars->grid);
	mlx_destroy_image(vars->init, vars->img.img);
	mlx_destroy_window(vars->init, vars->win);
	free(vars->init);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == 65451 || (keycode == 65453 && vars->offset >= 2))
	{
		mlx_clear_window(vars->init, vars->win);
		ft_memset(vars->img.addr, 0, WIN_HEIGHT * WIN_WIDTH * 4);
		if (keycode == 65451)
			vars->offset += 1;
		if (keycode == 65453)
			vars->offset -= 1;
		init_grid(vars->grid, vars->width, vars->height, vars->offset, &vars->img, vars->translate);
		mlx_put_image_to_window(vars->init, vars->win, vars->img.img, 0, 0);
	}
	if (keycode >= 65361 && keycode <= 65364)
	{
		mlx_clear_window(vars->init, vars->win);
		ft_memset(vars->img.addr, 0, WIN_HEIGHT * WIN_WIDTH * 4);
		if (keycode == 65361)
			vars->translate.x -= 5;
		if (keycode == 65362)
			vars->translate.y -= 5;
		if (keycode == 65363)
			vars->translate.x += 5;
		if (keycode == 65364)
			vars->translate.y += 5;
		init_grid(vars->grid, vars->width, vars->height, vars->offset, &vars->img, vars->translate);
		mlx_put_image_to_window(vars->init, vars->win, vars->img.img, 0, 0);
	}
	if (keycode == 65307)
	{
		destroy_map(vars->grid);
		mlx_destroy_image(vars->init, vars->img.img);
		mlx_destroy_window(vars->init, vars->win);
		free(vars->init);
		exit(0);
	}
	if (keycode == 113)
	{
		mlx_clear_window(vars->init, vars->win);
		ft_memset(vars->img.addr, 0, WIN_HEIGHT * WIN_WIDTH * 4);
		vars->degree += 3;
		rotate_matrix(vars->grid, vars->degree, vars->width, vars->height, &vars->img, vars->offset);
		mlx_put_image_to_window(vars->init, vars->win, vars->img.img, 0, 0);
	}
	if (keycode == 122)
	{
		mlx_clear_window(vars->init, vars->win);
		ft_memset(vars->img.addr, 0, WIN_HEIGHT * WIN_WIDTH * 4);
		vars->translate.z -= 5;
		init_grid(vars->grid, vars->width, vars->height, vars->offset, &vars->img, vars->translate);
		mlx_put_image_to_window(vars->init, vars->win, vars->img.img, 0, 0);
	}
	return (0);
}
