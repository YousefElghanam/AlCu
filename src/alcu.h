/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: netrunner <netrunner@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:52:41 by netrunner         #+#    #+#             */
/*   Updated: 2025/10/26 18:17:06 by netrunner        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_H
# define ALCU_H

#define BUFFER_SIZE 20000
#define ERROR "ERROR\n"
#define INVALID "invalid input\n"
#define ALLOC_ERR "allocation error\n"
#define READ_ERR "read error\n"


#define WIN 1
#define LOSE 0
#define PLAYER 1
#define AI 0

#ifndef VERBOSE
# define VERBOSE 0
#endif

#include <fcntl.h>
#include <stdbool.h>
#include "libft/libft.h"

void	error_msg(char *str);
char	**parse(int ac, char **av);
int		play(char **map);
void	ft_freesplit(char **split);
size_t	count_lines(char **split);

#endif