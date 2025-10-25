#include "alcu.h"

int	draw(long *heaps, size_t heap_count)
{
	long	i;

	for (size_t x = 0; x < heap_count; x++)
	{
		i = 0;
		printf("[%li]: ", heaps[x]);
		while (i++ < heaps[x])
			printf("| ");
		printf("\n");
		// ft_printf(1, "\n");
	}
	printf("\n");
	return (0);
}

void	perror_alloc(void)
{
	write(2, "allocation error\n", 17);
}

long	*make_heaps(char **map, size_t *count)
{
	size_t	heap_count;
	long	*heaps;

	heap_count = 0;
	while(map[heap_count])
		heap_count++;
	heaps = malloc(sizeof(long) * (heap_count + 1));
	if (!heaps)
		return (perror_alloc(), NULL);
	heap_count = 0;
	while (map[heap_count])
	{
		heaps[heap_count] = ft_atoi_but_better(map[heap_count]);
		if (heaps[heap_count] == 2147483648)
			return (ft_printf(2, "Invalid map\n"), free(heaps), NULL);
		heap_count++;
	}
	heaps[heap_count] = -1;
	*count = heap_count;
	return (heaps);
}

void think(void)
{
	int	i = 0;

	ft_printf(1, "AI is thinking\n");
	while (1)
	{
		if (i == 15005)
			return ;
		i += 19;
	}
}

int	solve_cur_map(long *heaps, size_t *heap_count)
{
	// think();
	if (heaps[*heap_count - 1] >= 1)
	{
		heaps[*heap_count - 1] -= 1;
		if (heaps[*heap_count - 1] == 0)
		{
			heaps[*heap_count - 1] = -1;
			*heap_count -= 1;
		}		// heap_count--;
		return (ft_printf(1, "AI takes 1\n"), 0);
	}
	return (1);
}

int	take_input(long *heaps, size_t *heap_count)
{
	char	input[10001];
	long	input_int;
	ssize_t	bytes_read;

	while (1)
	{
		ft_memset(input, 0, 10001);
		bytes_read = read(0, input, 10000);
		if (bytes_read == -1)
			return (ft_printf(2, "read error\n"), 1);
		if (bytes_read == 0)
			return (ft_printf(1, "Player quits, AI wins\n"), 1);
		input[bytes_read] = 0;
		input_int = ft_atoi_but_better(input);
		if (input_int == 2147483648 || input_int < 1 || input_int > 3)
		{
			printf("Player entered %zi\n", input_int);
			ft_printf(1, "Invalid input, please enter a number between 1 and 3\n");
			continue ;
		}
		// if (input_int < heaps[*heap_count - 1] && *heap_count == 1)
		// 	return (ft_printf(1, "AI takes %d\nYou lose\n", heaps[*heap_count - 1] - input_int), 0);
		if (input_int > heaps[*heap_count - 1])
		{
			ft_printf(1, "Not enough items in current heap, please enter a number between 1 and 3\n");
			continue ;
		}
		ft_printf(1, "Player takes %d\n", input_int);
		heaps[*heap_count - 1] -= input_int;
		if (heaps[*heap_count - 1] == 0 && *heap_count > 1)
		{
			heaps[*heap_count - 1] = -1;
			*heap_count -= 1;
		}
		if (*heap_count == 1 && heaps[1] == 1)
			ft_printf(1, "You win!!");
		break ;
	}
	return (0);
}

void	remove_empty_heap(long *heaps, size_t *heap_count)
{
	// printf("cur heap is %li === heap_count is %zu\n", heaps[*heap_count - 1], *heap_count);
	if (heaps[*heap_count - 1] == 0)
	{
		// printf("removed empty heap, heap_count is now %zu\n", *heap_count - 1);
		heaps[*heap_count - 1] = -1;
		*heap_count -= 1;
	}
}

int	check_heap(long *heaps, size_t heap_count, int is_player)
{
	(void)heaps;
	if (heap_count == 0 && is_player)
		return (ft_printf(1, "You lose\n"), 1);
	else if (heap_count == 0 && !is_player)
		return (ft_printf(1, "You win\n"), 1);
	// if (heap_count == 1 && heaps[0] == 1)
	// 	return (ft_printf(1, "You win\n"), 0);
	return (0);
}

int	play(char **map)
{
	size_t	heap_count;
	long	*heaps;

	heaps = make_heaps(map, &heap_count);
	if (!heaps)
		return (1);
	while (1)
	{
		if (draw(heaps, heap_count))
			return (free(heaps), 1);
		if (solve_cur_map(heaps, &heap_count))
			return (free(heaps), 1);
		remove_empty_heap(heaps, &heap_count);
		if (check_heap(heaps, heap_count, 0))
			return (free(heaps), 0);
		if (draw(heaps, heap_count))
			return (free(heaps), 1);
		if (take_input(heaps, &heap_count))
			return (free(heaps), 1);
		remove_empty_heap(heaps, &heap_count);
		if (check_heap(heaps, heap_count, 1))
			return (free(heaps), 0);
	}
}