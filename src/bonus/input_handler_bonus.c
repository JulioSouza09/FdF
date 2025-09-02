/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:43:49 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/16 18:13:33 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	usage_error(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" <filename>", 2);
}

int	valid_suffix(char *filename)
{
	const char	*suffix = ".fdf";
	char		*result;

	open_correctly(filename);
	result = ft_strrchr(filename, '.');
	if (ft_strncmp(result, suffix, ft_strlen(result)) == 0)
		return (1);
	return (0);
}

int	open_correctly(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("fdf");
		exit(errno);
	}
	return (fd);
}
