/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:42:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/12 14:16:28 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define TRUE 1
# define FALSE 0
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# include <stdio.h>
# include <errno.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

typedef	struct	s_point
{
	int	z;
	int	color;
}	t_point;

typedef struct	s_map
{
	t_point	**z;
	int 	width;
	int		height;
}	t_map;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		end;
}	t_data;

typedef struct s_draw
{
	int	zoom;
	int	translate_x;
	int	translate_y;
	int	iso;
	int	z;
}	t_draw;

typedef struct	s_app
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	*map;
	t_draw	transform;
}	t_app;

typedef struct	s_math
{
	int	dx;
	int	dy;
	int	p;
	int	dir;
}	t_math;

typedef struct	s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_line;

/***** Input handler *****/
void	usage_error(char *str);
int		valid_suffix(char *filename);
int		open_correctly(char *filename);

/***** File handler *****/
t_map	*get_map(char *filename);

/***** Map creator *****/
void	destroy_map(t_map *map);

/***** Map utils *****/
int		get_dimensions(int fd, int *width, int *height);
void	free_z(t_point **z, int position);
t_point	**get_z(int fd, t_map *map);
t_point	*get_file_values(char **line_split, int width);

/***** Utils *****/
int		ft_atoi_hex(char *nbr);
void	ft_swap(int *a, int *b);

/***** Init app *****/
t_app	*init_app(char *filename);
int	close_program(t_app *program);

/***** Draw line *****/
void	draw_line(t_line coords, t_data *data, t_app *app);

/***** Draw utils *****/
t_line	init_coords(int x0, int y0, int x1, int y1);
void	center_axis(t_line *coords, t_map *map);
void	zoom(t_line *coords, int *z0, int *z1, t_draw *apply);
void	center(t_line *coords);
void	update_z(int *z, int value);
int		translate(t_line *coords, t_draw *transform);

/***** Render *****/
int	render(t_app *app);
void	isometric(int *x, int *y, int z);

/***** Key handler *****/
void	init_hooks(t_app *app);

#endif
