/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:47:16 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 11:39:52 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//#define START_COLOR 0xc31432
//#define	END_COLOR 0x240b36
#define END_COLOR 0xcc5333
#define	START_COLOR 0x23074d

int	get_new_color(t_color color1, t_color color2, float percent)
{
	t_color	result;

	result.r = color1.r + percent * (color2.r - color1.r);
	result.g = color1.g + percent * (color2.g - color1.g);
	result.b = color1.b + percent * (color2.b - color1.b);
	return (result.r << 16 | result.g << 8 | result.b);
}

void	get_rgb(int color, t_color *new_color)
{
	new_color->r = ((color >> 16) & 0xFF);
	new_color->g = ((color >> 8) & 0xFF);
	new_color->b = (color & 0xFF);
}

int	create_color(int current_z, int z_range, int min_z)
{
	t_color	color1;
	t_color	color2;
	int		index;

	get_rgb(START_COLOR, &color1);
	get_rgb(END_COLOR, &color2);
	index = current_z - min_z;
	return (get_new_color(color1, color2, (float)index / z_range));

}
