/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:25:01 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/07/30 13:26:36 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	count_lines(char *filename)
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
