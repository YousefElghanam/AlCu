
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
		/* if (solve(map))
			return (1); */
		return (0);
	}
	write (2, "invalid input\n", 15);
	return (0);
}
