/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:42:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/07 13:03:44 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define TRUE 1

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

/***** Init app *****/
t_app	*init_app(char *filename);
void	close_program(t_app *program);

#endif
