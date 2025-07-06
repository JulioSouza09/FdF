/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/05 17:43:01 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "fdf.h"

#define X_START 800
#define Y_START 100
#define OFFSET 20
#define WIN_WIDTH 1600
#define WIN_HEIGHT 900

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	dst = data->addr + (y * data->line_len) + (x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

void	init_grid(t_point **array, int width, int height)
{
	int	i;
	int	j;
	t_point	start;

	i = 0;
	init_point(&start, X_START, Y_START);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			init_point(&array[i][j], start.x, start.y);
			array[i][j].y -= round((array[i][j].z * (OFFSET / 7)));
			start.x += round(OFFSET + (OFFSET * 0.16));
			start.y += round((OFFSET / 2) + ((OFFSET / 2) * 0.75));
			++j;
		}
		start.x = X_START - ((OFFSET * (i + 1)) + ((OFFSET * 0.4)* (i+1)));
		start.y = Y_START + ((OFFSET / 2) * (i + 1)) + ((OFFSET * 0.57) * (i+1));
		++i;
	}
}

void	draw_line(int x_start, int y_start, int x_end, int y_end, t_data *img_data)
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
		ft_pixel_put(img_data, pixel, y, 0xFFFFFF);
		--pixel;
	}
	while (pixel < x_end)
	{
		y = (delta_y / delta_x) * (pixel - x_start) + y_start;
		ft_pixel_put(img_data, pixel, y, 0xFFFFFF);
		++pixel;
	}
}

void	print_grid(void *mlx, void *win_ptr, t_point **array, int width, int height)
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

void	free_matrix(t_point **matrix, int position)
{
	int	i;

	i = 0;
	while (i < position)
		free(matrix[i++]);
}

static int	count_eol(char	*str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j++] == '\n')
			++i;
	}
	return (i);
}

static int	count_lines(char *filename)
{
	int		fd;
	int		bytes_read;
	int		count;
	char	buffer[1025];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(errno);
	}
	bytes_read = 1;
	count = 0;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, 1024);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		count += count_eol(buffer);
	}
	close(fd);
	return (count);
}


t_point	**get_map(int n_lines, int fd, int *w)
{
	t_point	**result;
	char	**line;
	int	i;

	result = malloc(sizeof(t_point *) * (n_lines + 1));
	if (!result)
		return (NULL);
	result[n_lines] = NULL;
	i = 0;
	while (i < n_lines)
	{
		line = ft_split(get_next_line(fd), ' ');;
		if (i == 0)
			*w = count_matrix(line);
		ft_printf("*w = %d\n", *w);
		if (line)
			result[i] = get_line_values(line);	
		++i;
	}
	return (result);
}

int	count_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i] != NULL)
		++i;
	return (i);
}

t_point	*get_line_values(char **splited_line)
{
	t_point	*result;
	int		i;
	int		len;

	len = count_matrix(splited_line);
	result = malloc(sizeof(t_point) * len);
	if (!result)
		return (NULL);
	i = 0;
	while (splited_line[i] != NULL)
	{
		result[i].z = ft_atoi(splited_line[i]);
		++i;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	void	*init;
	void	*win;
	t_point	**grid;
	int		fd;
	int		lines;
	int		count;
	t_data	img;

	if (argc < 2)
	{
		ft_printf("Usage: %s <filename> [ case_size z_size ]\n", argv[0]);
		return (1);
	}
	lines = count_lines(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (errno);
	}
	grid = get_map(lines, fd, &count);
	init = mlx_init();
	win = mlx_new_window(init, WIN_WIDTH, WIN_HEIGHT, "Test");
	ft_printf("lines = %d\n", lines);
	init_grid(grid, count, lines);
	img.img = mlx_new_image(init, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.end);
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < count - 1; j++)
		{
			draw_line(grid[i][j].x, grid[i][j].y, grid[i][j+1].x, grid[i][j+1].y, &img);

		}
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < lines - 1; j++)
		{
			draw_line(grid[j][i].x, grid[j][i].y, grid[j+1][i].x, grid[j+1][i].y, &img);
		}
	}
	mlx_put_image_to_window(init, win, img.img, 0, 0);
	//print_grid(init, win, grid, count, lines);
	// draw_line(init, win, 300, 125, 250, 150);
	mlx_loop(init);
	free(grid);
	close(fd);
	return (0);
}
