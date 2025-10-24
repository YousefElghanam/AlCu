#include "alcu.h"

void	perror_alloc(void)
{
	write(2, "allocation error\n", 17);
}

int	*make_heaps(char **map, size_t *count)
{
	size_t	heap_count;
	int		*heaps;

	heap_count = 0;
	while(map[heap_count])
		heap_count++;
	heaps = malloc(sizeof(int) * (heap_count + 1));
	if (!heaps)
		return (perror_alloc(), 1);
	heap_count = 0;
	while (map[heap_count])
	{
		heaps[heap_count] = ft_atoi(map[heap_count]);
		heap_count++;
	}
	heaps[heap_count] = -1;
	*count = heap_count;
	return (heaps);
}

int	play(char **map)
{
	size_t	heap_count;
	int		*heaps;

	heaps = make_heaps(map, &heap_count);
	if (!heaps)
		return (1);
	while (1)
	{
		
	}
}