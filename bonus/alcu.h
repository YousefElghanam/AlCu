#ifndef ALCU_H
# define ALCU_H

#define BUFFER_SIZE 100000
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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include "libft/libft.h"

/* utils */
void	error_msg(char *str);

char	**parse(int ac, char **av);
int		play(char **map);


// Patrick

void	ft_freesplit(char **split);
size_t	count_lines(char **split);


#endif