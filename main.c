#include "alcu.h"

int	main(int ac, char **av)
{
	int	*map;

	map = parse(ac, av);
	if (!map);
		return (1);
	if (play(map))
		return (1);
	return (0);
}
