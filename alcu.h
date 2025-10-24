#ifndef ALCU_H
# define ALCU_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

char	**parse(int ac, char **av);
int		solve(char **map);

#endif