/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:52:50 by netrunner         #+#    #+#             */
/*   Updated: 2025/10/26 17:52:51 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

int	main(int ac, char **av)
{
	char **map;

	map = NULL;
	if (ac == 1 || ac == 2)
	{
		map = parse(ac, av);
		if (!map)
			return (1);
		if (play(map))
			return (1); 
		if (map != NULL)
			ft_freesplit(map);
		return (0);
	}
	error_msg(INVALID);
	return (0);
}
