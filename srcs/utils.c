/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:36:42 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/08/11 18:48:05 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			result += nbr[i] - 'a' + 10;
		else if (nbr[i] >= 'A' && nbr[i] <= 'F')
			result += nbr[i] - 'A' + 10;
		else if (nbr[i] >= '0' && nbr[i] <= '9')
			result += nbr[i] - '0';
		++i;
	}
	return (result);
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
