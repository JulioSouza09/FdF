/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:42:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/06 11:51:33 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define TRUE 1

# include <stdio.h>
# include <errno.h>
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

/***** Input handler *****/
void	usage_error(char *str);
int		valid_suffix(char *filename);
int		open_correctly(char *filename, char *on_failure);

/***** File handler *****/
int		get_height(char *filename);
int		get_width(char *filename);
t_map	*get_map(char *filename);
void	destroy_map(t_map *map);
#endif
