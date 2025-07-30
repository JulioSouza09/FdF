/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:52:31 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 15:33:48 by jcesar-s         ###   ########.fr       */
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

void	destroy_map(t_point **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map[i]);
	free(map);
}

int	valid_suffix(char *filename)
{
	const char	*suffix = ".fdf";
	char		*file;

	file = ft_strrchr(filename, '.');
	if (!file || ft_strncmp(suffix, file, ft_strlen(suffix)))
		return (0);
	return (1);
}

int	open_file_correctly(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("fdf");
		exit (errno);
	}
	return (fd);
}
