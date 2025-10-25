#include "alcu.h"

int	main(int ac, char **av)
{
	char	**map;

	map = NULL;
	map = parse(ac, av);
	if (!map)
		return (1);
	if (play(map))
		return (ft_freesplit(map), 1);
	ft_freesplit(map);
	return (0);
}
