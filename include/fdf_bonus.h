/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:42:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/02 12:56:44 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H
# define TRUE 1
# define FALSE 0
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define KEYPRESS 2
# define DESTROYNOTIFY 17
# define ESC 65307
# define MINUS 65453
# define PLUS 65451
# define O 111
# define I 105
# define Z 122
# define X 120
# define A 97
# define D 100
# define ARROWUP 65362
# define ARROWDOWN 65364
# define ARROWLEFT 65361
# define ARROWRIGHT 65363
# define TRANSLATE_STEP 10
# define Z_FACTOR 0.5
# define ZOOM_FACTOR 1
# define ROTATION_FACTOR 5

# include <stdio.h>
# include <errno.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

typedef struct s_point
{
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	t_point	**z;
	int		width;
	int		height;
	int		z_min;
	int		z_max;
}	t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		end;
}	t_data;

typedef struct s_draw
{
	int		zoom;
	int		translate_x;
	int		translate_y;
	int		iso;
	float	z;
	float	angle;
}	t_draw;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	*map;
	t_draw	transform;
}	t_app;

typedef struct s_math
{
	int	dx;
	int	dy;
	int	p;
	int	dir;
}	t_math;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_line;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/***** Input handler *****/
void	usage_error(char *str);
int		valid_suffix(char *filename);
int		open_correctly(char *filename);

/***** File handler *****/
t_map	*get_map(char *filename);

/***** Map creator *****/
void	destroy_map(t_map *map);

/***** Map utils *****/
//int		get_dimensions(int fd, int *width, int *height, int *min, int *max);
int		get_dimensions(int fd, t_map *map);
void	free_z(t_point **z, int position);
t_point	**get_z(int fd, t_map *map);

/***** Utils *****/
int		ft_atoi_hex(char *nbr);
void	ft_swap(int *a, int *b);
void	get_min_max(t_map *map, int *min, int *max);

/***** Init app *****/
t_app	*init_app(char *filename);
int		close_program(t_app *program);

/***** Draw line *****/
void	draw_line(t_line coords, t_data *data, t_app *app);

/***** Draw utils *****/
t_line	init_coords(int x0, int y0, int x1, int y1);
void	center_axis(t_line *coords, t_map *map);
void	center(t_line *coords);
double	degrees_to_rad(double degree);

/***** Render *****/
int		render(t_app *app);

/***** Key handler *****/
void	init_hooks(t_app *app);

/***** Colors *****/
int		create_color(int current_z, int z_range, int min_z);

/***** Map transformer *****/
void	rotate_x(double angle, int *x, int *y, int *z);
void	zoom(t_line *coords, int *z0, int *z1, t_draw *apply);
void	isometric(int *x, int *y, int z);
float	get_z_increment(int z, float factor);
int		translate(t_line *coords, t_draw *transform);

/***** Events *****/
void	handle_zoom(int keycode, t_app *app);
void	handle_translation(int keycode, t_app *app);
void	handle_projection(int keycode, t_app *app);
void	handle_z(int keycode, t_app *app);
void	handle_rotation(int keycode, t_app *app);

#endif
