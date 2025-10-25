#ifndef ALCU_H
# define ALCU_H

#define BUFFER_SIZE 100000
#define ERROR "ERROR\n"

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
void	perror_alloc(void);

char	**parse(int ac, char **av);
int		play(char **map);


// Patrick

void	ft_freesplit(char **split);
size_t	count_lines(char **split);


#endif