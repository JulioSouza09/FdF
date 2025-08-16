/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:47:13 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 11:21:53 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	count_columns(char const *str, char delimeter, int *min, int *max)
{
	size_t	len;
	int		z;

	len = 0;
	while (*str)
	{
		while (*str == delimeter && *str)
			++str;
		if (*str)
		{
			z = ft_atoi(str);
			if (z > *max)
				*max = z;
			if (z < *min)
				*min = z;
			++len;
		}
		while (*str != delimeter && *str)
			++str;
	}
	return (len);
}

int	get_dimensions(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	map->width = count_columns(line, ' ', &map->z_min, &map->z_max);
	map->height = 1;
	while (TRUE)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)count_columns(line, ' ', &map->z_min, &map->z_max) != map->width)
		{
			ft_putendl_fd("Invalid map", 2);
			free(line);
			return (-1);
		}
		map->height += 1;
	}
	return (0);
}

t_point	*get_file_values(char **line_split, t_map *map)
{
	t_point	*values;
	char	*color;
	int		i;

	values = malloc(sizeof(t_point) * map->width);
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
			values[i].color = create_color(values[i].z, map->z_max - map->z_min, map->z_min);
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
		z[i] = get_file_values(ft_split(line, ' '), map);
		free(line);
		if (!z[i++])
		{
			free_z(z, i - 1);
			return (NULL);
		}
	}
	return (z);
}
