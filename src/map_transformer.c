/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transformer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:37 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/02 12:35:25 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_line *coords, int *z0, int *z1, int apply)
{
	if (apply < 1)
	{
		apply = 1;
		return ;
	}
	else if (apply > 100)
	{
		apply = 100;
		return ;
	}
	*z0 *= apply;
	*z1 *= apply;
	coords->x0 *= apply;
	coords->y0 *= apply;
	coords->x1 *= apply;
	coords->y1 *= apply;
}

void	isometric(int *x, int *y, int z)
{
	int	tmp;

	tmp = *x;
	*x = (tmp - *y) * cos(0.60);
	*y = (tmp + *y) * sin(0.60) - z / 10;
}
