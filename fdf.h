/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:42:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 15:35:13 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"

# define X_START 800
# define Y_START 100
# define OFFSET 1
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define READ_BUF_SIZE 2048
# define TRUE 1
# define FALSE 0

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		x2;
	int		y2;
	int		color;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		end;
}	t_data;

typedef struct s_dimension
{
	int	width;
	int	height;
}	t_dimension;

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

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

typedef struct s_vars
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

/* Drawing functions */
void	ft_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(int x_start, int y_start, int x_end, int y_end, t_data *img_data, int color);

/* Point and grid functions */
void	init_grid(t_point **array, int width, int height, float offset, t_data *test, t_point translate);

/* File handling functions */
int		valid_suffix(char *filename);
int		open_file_correctly(char *filename);
void	destroy_map(t_point **map);
t_point	**get_map(char *filename, t_dimension *dimensions);

/* Matrix functions */
int		count_matrix(char **matrix);
int		ft_atoi_hex(char *nbr);

/* Event handlers */
int		handle_no_event(t_vars *vars);
int		handle_buttonpress(int button, int x, int y, t_vars *vars);
int		close_win(t_vars *vars);
int		handle_keypress(int keycode, t_vars *vars);

/* Rotation functions */
double	degrees_to_radians(double degree);
t_coord	rotate_point(double degree, int x, int y, int z);
void	rotate_matrix(t_point **map, int degree, int width, int height, t_data *img, int offset);

#endif
