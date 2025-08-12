/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:47:13 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/12 18:29:45 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_dimensions(int fd, int *width, int *height)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	*width = count_words(line, ' ');
	*height = 1;
	while (TRUE)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)count_words(line, ' ') != *width)
		{
			ft_putendl_fd("Invalid map", 2);
			free(line);
			return (-1);
		}
		*height += 1;
	}
	return (0);
}

t_point	*get_file_values(char **line_split, int width)
{
	t_point	*values;
	char	*color;
	int		i;

	values = malloc(sizeof(t_point) * width);
	if (!values)
		return (NULL);
	i = 0;
	while (line_split[i])
	{
		values[i].z = ft_atoi(line_split[i]);
		color = ft_strrchr(line_split[i], ',');
		if (color)
			values[i].color = ft_atoi_hex(++color);
		else
			values[i].color = 0xE9F1F7 + values[i].z * 5;
		free(line_split[i++]);
	}
	free(line_split);
	return (values);
}

void	free_z(t_point **z, int position)
{
	int	i;

	i = 0;
	while (i < position)
		free(z[i++]);
	free(z);
}

t_point	**get_z(int fd, t_map *map)
{
	t_point	**z;
	char	*line;
	int		i;

	z = malloc(sizeof(t_point *) * map->height);
	if (!z || fd == -1)
		return (NULL);
	i = 0;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		z[i] = get_file_values(ft_split(line, ' '), map->width);
		free(line);
		if (!z[i++])
		{
			free_z(z, i - 1);
			return (NULL);
		}
	}
	return (z);
}
