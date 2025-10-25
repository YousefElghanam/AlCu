
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
		for(int i = 0; map[i]; i++)
			printf("%s\n", map[i]);
		ft_freesplit(map);
		return (0);
	}
	write (2, "invalid input\n", 15);
	return (0);
}
