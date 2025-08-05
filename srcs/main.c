/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:41:53 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/05 16:47:18 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		usage_error(argv[0]);
		return (1);
	}
	if (!valid_suffix(argv[1]))
	{
		ft_putendl_fd("FdF: Invalid filetype. Expected '.fdf' file.", 2);
		return (2);
	}
	return (0);
}
