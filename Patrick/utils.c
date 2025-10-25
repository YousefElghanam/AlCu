/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:12:55 by pjelinek          #+#    #+#             */
/*   Updated: 2025/10/25 03:10:59 by netrunner        ###   ########.fr       */
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
/* 
int	ft_strcheck(const char *str, int c)
{
	unsigned char	letter;
	int				i;

	i = 0;
	letter = (unsigned char) c;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == letter)
			i++;
		else
			return (0);
	}
	return (1);
}

int	count_letters(char *str, int c)
{
	unsigned char	letter;
	unsigned int	count;
	size_t			i;

	letter = (unsigned char) c;
	count = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == letter)
			count++;
		i++;
	}
	return (count);
}

int	find_char(char *str, int c)
{
	unsigned char	letter;
	size_t			i;

	letter = (unsigned char) c;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == letter)
			return (i);
		i++;
	}
	return (0);
}

int	count_lines(char **split)
{
	int	count;

	count = 0;
	if (split || *split)
	{
		while (split[count] != NULL)
			count++;
	}
	return (count);
}
 */