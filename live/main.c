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
		ft_freesplit(map);
		return (0);
	}
	error_msg(INVALID);
	return (0);
}
