/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:12:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/10/26 17:53:07 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

void	ft_freesplit(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

size_t	count_lines(char **split)
{
	size_t	count;

	count = 0;
	if (split || *split)
	{
		while (split[count] != NULL)
			count++;
	}
	return (count);
}