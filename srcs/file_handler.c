/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:17:52 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/06 12:22:01 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open_correctly(filename, "exit");
	if (!fd)
		exit(errno);
	i = 0;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		free(line);
		++i;
	}
	close(fd);
	return (i);
}

int	get_width(char *filename)
{
	int		fd;
	int		width;
	char	*line;

	fd = open_correctly(filename, "return");
	if (!fd)
		return (-1);
	line = get_next_line(fd);
	width = count_words(line, ' ');
	while (TRUE)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)count_words(line, ' ') != width)
		{
			ft_putendl_fd("Invalid map\n", 2);
			free(line);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (width);
}

int	ft_atoi_hex(char *nbr)
{
	int	i;
	int	result;

	i = 0;
	if (!ft_strncmp("0x", nbr, 2))
		i += 2;
	result = 0;
	while (nbr[i])
	{
		result *= 16;
		if (nbr[i] >= 'a' && nbr[i] <= 'f')
			result += nbr[i] - 'a';
		else if (nbr[i] >= 'A' && nbr[i] <= 'F')
			result += nbr[i] - 'A';
		else if (nbr[i] >= '0' && nbr[i] <= '9')
			result += nbr[i] - '0';
		++i;
	}
	return (result);
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
			values[i].color = ft_atoi_hex(color);
		else
			values[i].color = 0xFFFFFF;
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

void	destroy_map(t_map *map)
{
	free_z(map->z, map->height);
	free(map);
}

t_point	**get_z(char *filename, t_map *map)
{
	t_point	**z;
	char	*line;
	int		fd;
	int		i;

	z = malloc(sizeof(t_point *) * map->height);
	fd = open_correctly(filename, "return");
	if (!z || !fd)
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
			return (free_z(z, i - 1), NULL);
	}
	close(fd);
	return (z);
}


t_map	*get_map(char *filename)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = get_height(filename);
	map->width = get_width(filename);
	if (map->width == -1)
	{
		free(map);
		exit(3);
	}
	map->z = get_z(filename, map);
	if (!map->z)
	{
		destroy_map(map);
		return (NULL);
	}
	return (map);
}

