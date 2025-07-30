/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:53:07 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 15:32:22 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	*handle_color(t_point *result, char *element)
{
	char	**color_case;
	int		j;	

	color_case = ft_split(element, ',');
	if (!color_case)
		return (NULL);
	j = 0;
	while (color_case[j] != NULL)
	{
		if (j == 0)
			result[j].color = ft_atoi_hex(color_case[1]);
		free(color_case[j++]);
	}
	free(color_case);
	return (result);
}

static t_point	*get_line_values(char **splited_line, t_dimension *dimensions)
{
	t_point	*result;
	int		i;

	result = malloc(sizeof(t_point) * dimensions->width);
	if (!result)
		return (NULL);
	i = 0;
	while (splited_line[i] != NULL)
	{
		result[i].z = ft_atoi(splited_line[i]);
		if (ft_strchr(splited_line[i], ','))
		{
			if (!handle_color(&result[i], splited_line[i]))
				return (NULL);
		}
		else
			result[i].color = 0xFFFFF3;
		free(splited_line[i++]);
	}
	free(splited_line);
	return (result);
}

static t_point	**parse_map(t_point **result, t_dimension *dimensions, int fd)
{
	int		i;
	char	*line;
	char	**line_split;

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
	return (result);
}

static int	count_lines(char *filename)
{
	int		fd;
	int		bytes_read;
	int		count;
	char	buffer[READ_BUF_SIZE + 1];
	int		i;

	fd = open_file_correctly(filename);
	count = 0;
	while (TRUE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		i = 0;
		while(buffer[i])
		{
			if (buffer[i++] == '\n')
				++count;
		}
	}
	close(fd);
	return (count);
}

t_point	**get_map(char *filename, t_dimension *dimensions)
{
	t_point	**result;
	int		fd;

	dimensions->height = count_lines(filename);
	fd = open_file_correctly(filename);
	result = malloc(sizeof(t_point *) * (dimensions->height + 1));
	if (!result)
		return (NULL);
	result[dimensions->height] = NULL;
	parse_map(result, dimensions, fd);	
	close(fd);
	return (result);
}
