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

#define X_START 400
#define Y_START 200
#define OFFSET 20


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
			array[i][j].y -= (array[i][j].z * 100);
			start.x += OFFSET + 5;
			start.y += (OFFSET / 2) + 10;
			++j;
		}
		start.x = X_START - ((OFFSET * (i + 1)) + (12 * (i+1)));
		start.y = Y_START + ((OFFSET / 2) * (i + 1)) + (17 * (i+1));
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

	i = 0;
	while (*str)
	{
		if (*str++ == '\n')
			++i;
	}
	return (i);
}

static int	count_lines(char *filename)
{
	int		fd;
	int		bytes_read;
	int		count;
	char	buffer[1024];

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
		*w = count_matrix(line);
		result[i] = get_line_values(line);	
		if (!result[i])
		{
			free_matrix(result, i);
			exit(3);
		}
		++i;
	}
	return (result);
}

int	count_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
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
	ft_printf("%d\n", lines); 
	init = mlx_init();
	win = mlx_new_window(init, 1000, 1000, "Test");
	init_grid(grid, count, lines);
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < count - 1; j++)
		{
			draw_line(init, win, grid[i][j].x, grid[i][j].y, grid[i][j+1].x, grid[i][j+1].y);

		}
		ft_printf("\n");
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < lines - 1; j++)
		{
			draw_line(init, win, grid[j][i].x, grid[j][i].y, grid[j+1][i].x, grid[j+1][i].y);
		}
		ft_printf("\n");
	}
	print_grid(init, win, grid, count, lines);
	// draw_line(init, win, 300, 125, 250, 150);
	mlx_loop(init);
	free(grid);
	close(fd);
	return (0);
}
