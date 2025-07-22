/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:41:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/22 14:49:34 by jcesar-s         ###   ########.fr       */
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
#define OFFSET 1
#define WIN_WIDTH 1600
#define WIN_HEIGHT 900
#define READ_BUF_SIZE 2048
#define TRUE 1
#define FALSE 0

typedef struct s_test
{
	t_point	**grid;
	int		lines;
	int		count;
	t_data	img;
	void	*init;
	void	*win;
	int		offset;
}	t_test;


void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	dst = data->addr + (y * data->line_len) + (x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
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
		ft_pixel_put(img_data, pixel, y, 0x7B8FBD);
		--pixel;
	}
	while (pixel < x_end)
	{
		y = (delta_y / delta_x) * (pixel - x_start) + y_start;
		ft_pixel_put(img_data, pixel, y, 0x7B8FBD);
		++pixel;
	}
}*/

void    draw_line(int x_start, int y_start, int x_end, int y_end, t_data *img_data, int color)
{
    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = (x_start < x_end) ? 1 : -1;
    int sy = (y_start < y_end) ? 1 : -1;
    int err = dx - dy;
    int err2;

    while (1)
    {
        ft_pixel_put(img_data, x_start, y_start, color);
        if (x_start == x_end && y_start == y_end)
            break;
        err2 = 2 * err;
        if (err2 > -dy)
        {
            err -= dy;
            x_start += sx;
        }
        if (err2 < dx)
        {
            err += dx;
            y_start += sy;
        }
    }
}


void	init_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

void	init_grid(t_point **array, int width, int height, float offset, t_data *test, t_point translate)
{
	int	i;
	int	j;
	t_point	start;
	t_point	position;
	t_point	tmp;

	position.x = width / 2;
	position.y = height / 2;
	tmp.x = 0 + (position.y - position.x) * (offset * 2);
	tmp.y = 0 - (position.x + position.x) * offset;
	i = 0;
	init_point(&start, tmp.x, tmp.y);
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			init_point(&array[i][j], start.x + translate.x, start.y + translate.y);
			if (array[i][j].z != 0)
				array[i][j].z += translate.z;
			array[i][j].y -= round((array[i][j].z) * (offset / 7));
			//start.x += round(offset * 1.16);
			//start.y += round((offset / 2) * 1.75);
			start.x += offset * 2;
			start.y += offset;
			if (j >= 1)
				draw_line(array[i][j - 1].x, array[i][j - 1].y, array[i][j].x, array[i][j].y, test, array[i][j].color);
			if (i >= 1)
				draw_line(array[i - 1][j].x, array[i - 1][j].y, array[i][j].x, array[i][j].y, test, array[i][j].color);
			++j;
		}
		++i;
		//start.x = round(X_START - ((offset * i) + (offset * 0.4 * i)));
		//start.y = round(Y_START + ((offset / 2) * i) + (offset * 0.57 * i));
		//start.x = X_START - (((offset*2) * i));
		//start.y = Y_START + ((offset * i));
		start.x = tmp.x - (((offset*2) * i));
		start.y = tmp.y + ((offset * i));
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

int	valid_suffix(char *filename)
{
	const char	*suffix = ".fdf";
	char		*file;

	file = ft_strrchr(filename, '.');
	if (!file || ft_strncmp(suffix, file, ft_strlen(suffix)))
		return (0);
	return (1);
}

int	open_file_correctly(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("fdf");
		exit (errno);
	}
	return (fd);
}

static int	count_lines(char *filename)
{
	int		fd;
	int		bytes_read;
	int		count;
	char	buffer[READ_BUF_SIZE + 1];
	int		i;

	fd = open_file_correctly(filename);
	count = 0;
	while (TRUE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		i = 0;
		while(buffer[i])
		{
			if (buffer[i++] == '\n')
				++count;
		}
	}
	close(fd);
	return (count);
}

void	destroy_map(t_point **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map[i]);
	free(map);
}

t_point	**get_map(char *filename, t_dimension *dimensions)
{
	t_point	**result;
	char	**line_split;
	char	*line;
	int		i;
	int		fd;

	dimensions->height = count_lines(filename);
	fd = open_file_correctly(filename);
	result = malloc(sizeof(t_point *) * (dimensions->height + 1));
	if (!result)
		return (NULL);
	result[dimensions->height] = NULL;
	i = 0;
	while (i < dimensions->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_split = ft_split(line, ' ');
		free(line);
		if (!line_split)
		{
			destroy_map(result);
			return (NULL);
		}
		if (i == 0)
			dimensions->width = count_matrix(line_split);
		result[i] = get_line_values(line_split, dimensions);	
		++i;
	}
	close(fd);
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

int	ft_atoi_hex(char *nbr)
{
	int	i;
	int	result;

	i = 0;
	if (!ft_strncmp("0x", nbr, 2))
		i += 2;
	result = 0;
	while (nbr[i])
	{
		result *= 16;
		if (nbr[i] >= 'a' && nbr[i] <= 'f')
			result += nbr[i] - 'a';
		else if (nbr[i] >= 'A' && nbr[i] <= 'F')
			result += nbr[i] - 'A';
		else if (nbr[i] >= '0' && nbr[i] <= '9')
			result += nbr[i] - '0';
		++i;
	}
	return (result);
}

t_point	*get_line_values(char **splited_line, t_dimension *dimensions)
{
	t_point	*result;
	char	**color_case;
	int		i;
	int		j;

	result = malloc(sizeof(t_point) * dimensions->width);
	if (!result)
		return (NULL);
	i = 0;
	while (splited_line[i] != NULL)
	{
		result[i].z = ft_atoi(splited_line[i]);
		if (ft_strchr(splited_line[i], ','))
		{
			color_case = ft_split(splited_line[i], ',');
			if (!color_case)
				return (NULL);
			j = 0;
			while (color_case[j] != NULL)
			{
				if (j == 0)
					result[i].color = ft_atoi_hex(color_case[1]);
				free(color_case[j++]);
			}
			free(color_case);
		}
		free(splited_line[i++]);
	}
	free(splited_line);
	return (result);
}

typedef struct	s_vars
{
	void	*init;
	void	*win;
	t_point	**grid;
	int		width;
	int		height;
	float	offset;
	t_point	translate;
	t_data	img;
	int		degree;
}	t_vars;



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

double	degrees_to_radians(double degree)
{
	return (degree * (M_PI / 180));
}

t_coord		rotate_point(double degree, int x, int y, int z)
{
	t_coord result;
	double dg;

	dg = degrees_to_radians(degree);
	result.x = x + WIN_WIDTH / 2;
	result.y = y * cos(dg) + z * sin(dg) + WIN_HEIGHT / 2;
	result.z = z * cos(dg) - y * sin(dg);
	return (result);
}

void	rotate_matrix(t_point **map, int degree, int width, int height, t_data *img, int offset)
{
	int	i;
	int	j;
	
	t_coord	point;

	i = 0;
	(void) offset;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			//printf("before: x = %d y = %d\n", map[i][j].x, map[i][j].y);
			//int	z = round(map[i][j].z * (offset / 7));
			point = rotate_point(degree, map[i][j].x, map[i][j].y, map[i][j].z);
			//printf("point: %d\n", point.z);
			map[i][j].x2 = point.x;
			map[i][j].y2 = point.y - point.z; //- round(point.z * (offset / 7);
			//printf("after: x = %d y = %d\n", map[i][j].x, map[i][j].y);
			if (j >= 1)
				draw_line(map[i][j - 1].x2, map[i][j - 1].y2, map[i][j].x2, map[i][j].y2, img, map[i][j].color);
			if (i >= 1)
				draw_line(map[i - 1][j].x2, map[i - 1][j].y2, map[i][j].x2, map[i][j].y2, img, map[i][j].color);
			++j;
		}
		++i;
	}
}

int	handle_keypress(int keycode, t_vars *vars)
{
	//ft_printf("keycode = %d\n", keycode);
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

int	main(int argc, char **argv)
{
	void	*init;
	void	*win;
	t_data	img;
	t_point	**grid;
	t_dimension	dimensions;
	t_vars	vars;

	if (argc < 2)
	{
		ft_printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	if (!valid_suffix(argv[1]))
	{
		ft_putendl_fd("fdf: invalid filetype", 2);
		return (2);
	}
	grid = get_map(argv[1], &dimensions);
	init = mlx_init();
	win = mlx_new_window(init, WIN_WIDTH, WIN_HEIGHT, "Test");
	img.img = mlx_new_image(init, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.end);
	vars.init = init;
	vars.win = win;
	vars.grid = grid;
	vars.width = dimensions.width;
	vars.height = dimensions.height;
	vars.offset = OFFSET;
	vars.img = img;
	vars.translate.x = 0;
	vars.translate.y = 0;
	vars.translate.z = 0;
	vars.degree = 1;
	printf("%f\n", degrees_to_radians(265));
	init_grid(grid, dimensions.width, dimensions.height, OFFSET, &img, vars.translate);
	mlx_put_image_to_window(init, win, img.img, 0, 0);
	mlx_loop_hook(vars.win, handle_no_event, &vars);
	mlx_hook(vars.win, 2, 	1L<<0, handle_keypress, &vars);
	mlx_hook(vars.win, 4, 1L<<2, handle_buttonpress, &vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_loop(init);
	return (0);
}
