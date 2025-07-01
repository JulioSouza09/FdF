/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/06/26 16:36:30 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X_START 300
#define Y_START 100
#define OFFSET 50

typedef	struct s_point
{
	int	x;
	int	y;
	int	z;
} t_point;

void	init_point(t_point *point, int x, int y, int z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

void	init_grid(t_point array[][6], int width, int height)
{
	int	i;
	int	j;
	t_point	start;

	i = 0;
	init_point(&start, X_START, Y_START, 0);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			init_point(&array[i][j], start.x, start.y, rand() % 100);
			array[i][j].y += array[i][j].z;
			start.x += OFFSET;
			start.y += (OFFSET / 2);
			++j;
		}
		start.x = X_START - (OFFSET * (i + 1));
		start.y = Y_START + ((OFFSET / 2) * (i + 1));
		++i;
	}
}

void	draw_line(void *mlx, void *win, int x_start, int y_start, int x_end, int y_end)
{
	float	delta_x;
	float	delta_y;
	float	 y;
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
		mlx_pixel_put(mlx, win, pixel, y, 0xFFFFFF);
		++pixel;
	}
	while (pixel < x_end)
	{
		y = (delta_y / delta_x) * (pixel - x_start) + y_start;
		mlx_pixel_put(mlx, win, pixel, y, 0xFFFFFF);
		++pixel;
	}

}

void	print_grid(void *mlx, void *win_ptr, t_point array[][6], int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(mlx, win_ptr, array[i][j].x, array[i][j].y, 0xFFFFFF);
			++j;
		}
		++i;
	}
}

int	main(void)
{
	void	*init;
	void	*win;
	t_point	grid[6][6];

	srand(time(0));
	init = mlx_init();
	win = mlx_new_window(init, 600, 600, "Test");
	init_grid(grid, 6, 6);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("{ x=%d, y=%d }", grid[i][j].x, grid[i][j].y);
			draw_line(init, win, grid[i][j].x, grid[i][j].y, grid[i][j+1].x, grid[i][j+1].y);

		}
		printf("\n");
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("{ x=%d, y=%d }", grid[j][i].x, grid[j][i].y);
			draw_line(init, win, grid[j][i].x, grid[j][i].y, grid[j+1][i].x, grid[j+1][i].y);

		}
		printf("\n");
	}
	print_grid(init, win, grid, 6, 6);
	// draw_line(init, win, 300, 125, 250, 150);
	mlx_loop(init);
	return (0);
}
