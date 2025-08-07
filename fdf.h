/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:42:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/07 18:31:29 by joel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define TRUE 1
# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# include <stdio.h>
# include <errno.h>
# include <mlx.h>
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

typedef struct	s_app
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	*map;
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
void	close_program(t_app *program);

/***** Draw line *****/
void	draw_line(t_line coords, t_data *data);

/***** Draw utils *****/
t_line	init_coords(int x0, int y0, int x1, int y1);

#endif
