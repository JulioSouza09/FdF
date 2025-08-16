/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:17:52 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 11:21:24 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*get_map(char *filename)
{
	t_map	*map;
	int		size_fd;
	int		parse_fd;

	size_fd = open_correctly(filename);
	parse_fd = open_correctly(filename);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	if (get_dimensions(size_fd, map) == -1)
	{
		free(map);
		exit(3);
	}
	map->z = get_z(parse_fd, map);
	if (!map->z)
	{
		destroy_map(map);
		return (NULL);
	}
	return (map);
}

void	destroy_map(t_map *map)
{
	free_z(map->z, map->height);
	free(map);
}
