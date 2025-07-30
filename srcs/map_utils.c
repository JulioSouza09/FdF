/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:53:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 12:53:12 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i] != NULL)
		++i;
	return (i);
}

t_point	*get_line_values(char **splited_line, t_dimension *dimensions)
{
	t_point	*result;
	char	**color_case;
	int		i;
	int		j;

	result = malloc(sizeof(t_point) * dimensions->width);
	if (!result)
		return (NULL);
	i = 0;
	while (splited_line[i] != NULL)
	{
		result[i].z = ft_atoi(splited_line[i]);
		if (ft_strchr(splited_line[i], ','))
		{
			color_case = ft_split(splited_line[i], ',');
			if (!color_case)
				return (NULL);
			j = 0;
			while (color_case[j] != NULL)
			{
				if (j == 0)
					result[i].color = ft_atoi_hex(color_case[1]);
				free(color_case[j++]);
			}
			free(color_case);
		}
		else
			result[i].color = 0xFFFFF3;
		free(splited_line[i++]);
	}
	free(splited_line);
	return (result);
}

void	destroy_map(t_point **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map[i]);
	free(map);
}

t_point	**get_map(char *filename, t_dimension *dimensions)
{
	t_point	**result;
	char	**line_split;
	char	*line;
	int		i;
	int		fd;

	dimensions->height = count_lines(filename);
	fd = open_file_correctly(filename);
	result = malloc(sizeof(t_point *) * (dimensions->height + 1));
	if (!result)
		return (NULL);
	result[dimensions->height] = NULL;
	i = 0;
	while (i < dimensions->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_split = ft_split(line, ' ');
		free(line);
		if (!line_split)
		{
			destroy_map(result);
			return (NULL);
		}
		if (i == 0)
			dimensions->width = count_matrix(line_split);
		result[i] = get_line_values(line_split, dimensions);	
		++i;
	}
	close(fd);
	return (result);
}
