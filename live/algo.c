#include "alcu.h"

int	draw(long *heaps, size_t heap_count, long *win_lose_arr)
{
	long	i;

	for (size_t x = 0; x < heap_count; x++)
	{
		if (heap_count == SIZE_MAX)
			break ;
		i = 0;
		printf("[%li]	: ", heaps[x]);
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
	if (!*map)
		return (NULL);
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

int	base_take_lose(long items)
{
	if (items == 1 || items == 2 || items == 3)
		return (items);
	else if (items % 4 == 1)
		return (1);
	else if (items % 4 == 2)
		return (2);
	else if (items % 4 == 3)
		return (3);
	else
		return (1);
}

int	base_take_win(long items)
{
	if ((items % 4 ) == 3)
		return (2);
	else if (items % 4 == 0)
		return (3);
	else
		return (1);
}

int	calc_moves(long *heaps, size_t heap_count, long *win_lose_arr)
{
	if (win_lose_arr[heap_count - 1] == WIN)
		return (base_take_win(heaps[heap_count - 1]));
	else
		return (base_take_lose(heaps[heap_count - 1]));
}

int	solve_cur_map(long *heaps, size_t *heap_count, long *win_lose_arr)
{
	think();
	int		moves = 1;

	moves = calc_moves(heaps, *heap_count, win_lose_arr);
	heaps[*heap_count - 1] -= moves;
	ft_printf(1, "AI takes %i\n", moves);
	return (0);
}

int	take_input(long *heaps, size_t *heap_count)
{
	char	input[10001];
	long	input_int;
	ssize_t	bytes_read;

	while (1)
	{
		ft_memset(input, 0, 10001);
		bytes_read = read(1, input, 10000);
		if (bytes_read == -1)
			return (ft_printf(2, "read error\n"), 1);
		if (bytes_read == 0)
			return (ft_printf(1, "Player quits, AI wins\n"), 1);
		input[bytes_read] = 0;
		input_int = ft_atoi_but_better(input);
		if (input_int == 2147483648 || input_int < 1 || input_int > 3)
		{
			ft_printf(1, "Invalid input, please enter a number between 1 and 3\n");
			continue ;
		}
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
	if (heaps[*heap_count - 1] == 0)
	{
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
	return (0);
}

long	*calc_win_lose_arr(long *heaps, size_t heap_count)
{
	long	*arr;

	arr = malloc(sizeof(long) * heap_count);
	if (!arr)
		return (NULL);
	arr[0] = WIN;
	for (size_t i = 1; i < heap_count; i++)
	{
		if (arr[i - 1] == WIN)
		{
			if (heaps[i - 1] % 4 == 1)
				arr[i] = LOSE;
			else
				arr[i] = WIN;
		}
		else if (arr[i - 1] == LOSE)
		{
			if (heaps[i - 1] >= 4 && heaps[i - 1] % 4 == 0) 
				arr[i] = LOSE;
			else
				arr[i] = WIN;
		}
	}
	return (arr);
}

int	play(char **map)
{
	size_t	heap_count;
	long	*heaps;
	long	*win_lose_arr;

	heaps = make_heaps(map, &heap_count);
	if (!heaps)
		return (perror_alloc(), 1);
	win_lose_arr = calc_win_lose_arr(heaps, heap_count);
	if (!win_lose_arr)
		return (free(heaps), perror_alloc(), 1);
	while (1)
	{
		if (draw(heaps, heap_count, win_lose_arr))
			return (free(heaps), free(win_lose_arr), 1);
		if (solve_cur_map(heaps, &heap_count, win_lose_arr))
			return (free(heaps), free(win_lose_arr), 1);
		if (check_heap(heaps, heap_count, AI))
			return (free(heaps), free(win_lose_arr), 0);
		remove_empty_heap(heaps, &heap_count);
		if (check_heap(heaps, heap_count, AI))
			return (free(heaps), free(win_lose_arr), 0);
		if (draw(heaps, heap_count, win_lose_arr))
			return (free(heaps), free(win_lose_arr), 1);
		if (take_input(heaps, &heap_count))
			return (free(heaps), free(win_lose_arr), 1);
		if (check_heap(heaps, heap_count, PLAYER))
			return (free(heaps), free(win_lose_arr), 0);
		remove_empty_heap(heaps, &heap_count);
		if (check_heap(heaps, heap_count, PLAYER))
			return (free(heaps), free(win_lose_arr), 0);
	}
}