#include "alcu.h"

int draw(long *heaps, size_t count, long *line_state)
{
	long i;

	for (size_t x = 0; x < count; x++)
	{
		if (count == SIZE_MAX)
			break;
		i = 0;
		ft_putchar_fd('[', 1);
		ft_putnbr_fd(heaps[x], 1);
		ft_putstr_fd("]	: ", 1);
		while (i++ < heaps[x])
			ft_putstr_fd("| ", 1);	
		ft_putchar_fd('\n', 1);
	}
	ft_putchar_fd('\n', 1);
	return (0);
}


long *make_heaps(char **map, size_t *count)
{
	size_t lines;
	long *heaps;

	lines = 0;
	if (!*map)
		return (NULL);
	while (map[lines])
		lines++;
	heaps = malloc(sizeof(long) * (lines + 1));
	if (!heaps)
		return (error_msg(ALLOC_ERR), NULL);
	lines = 0;
	while (map[lines])
	{
		heaps[lines] = ft_atoi_but_better(map[lines]);
		if (heaps[lines] == 2147483648)
			return (error_msg(INVALID), free(heaps), NULL);
		lines++;
	}
	heaps[lines] = -1;
	*count = lines;
	return (heaps);
}

void think(void)
{
	int i = 0;

	//ft_printf(1, "\tAI is thinking\n\n");
	while (1)
	{
		if (i == 15005)
			return;
		i += 105;
	}
}

int move_to_lose_line(long heaps)
{
	if (heaps == 1 || heaps == 2 || heaps == 3)
		return (heaps);
	else if (heaps % 4 == 1)
		return (1);
	else if (heaps % 4 == 2)
		return (2);
	else if (heaps % 4 == 3)
		return (3);
	else
		return (1);
}

int move_to_win_line(long heaps)
{
	if ((heaps % 4) == 3)
		return (2);
	else if (heaps % 4 == 0)
		return (3);
	else
		return (1);
}

int calc_moves(long *heaps, size_t count, long *line_state)
{
	if (line_state[count - 1] == WIN)
		return (move_to_win_line(heaps[count - 1]));
	else
		return (move_to_lose_line(heaps[count - 1]));
}

int solve_cur_map(long *heaps, size_t *count, long *line_state)
{
	think();
	int moves = 1;

	moves = calc_moves(heaps, *count, line_state);
	heaps[*count - 1] -= moves;
	ft_putstr_fd("AI takes ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int take_input(long *heaps, size_t *count)
{
	char input[10001];
	long input_int;
	ssize_t bytes_read;
	while (1)
	{
		ft_putstr_fd("Player input: ", 1);
		ft_memset(input, 0, 10001);
		bytes_read = read(1, input, 10000);
		if (bytes_read == -1)
			return (error_msg(READ_ERR), 1);
		if (bytes_read == 0)
			return (ft_putstr_fd("Player quits, AI wins\n", 1), 1);
		input[bytes_read] = 0;
		input_int = ft_atoi_but_better(input);
		if (input_int == 2147483648 || input_int < 1 || input_int > 3)
		{
			ft_putendl_fd("Invalid input, please enter a number between 1 and 3", 1);
			continue;
		}
		if (input_int > heaps[*count - 1])
		{
			ft_putendl_fd("Not enough heaps in heap,\nplease enter a number between 1 and 3", 1);
			continue;
		}
		heaps[*count - 1] -= input_int;
		if (heaps[*count - 1] == 0 && *count > 1)
		{
			heaps[*count - 1] = -1;
			*count -= 1;
		}
		if (*count == 1 && heaps[1] == 1)
		ft_putendl_fd("\nYou win!", 1);
		break;
	}
	return (0);
}

void remove_empty_heap(long *heaps, size_t *count)
{
	if (heaps[*count - 1] == 0)
	{
		heaps[*count - 1] = -1;
		*count -= 1;
	}
}

int check_heap(size_t count, int is_player)
{
	if (count == 0 && is_player)
		return (ft_putendl_fd("\nYou lose!", 1), 1);
	else if (count == 0 && !is_player)
		return (ft_putendl_fd("\nYou win!", 1), 1);
	return (0);
}

long *calc_line_state(long *heaps, size_t count)
{
	long *arr;

	arr = malloc(sizeof(long) * count);
	if (!arr)
		return (NULL);
	arr[0] = WIN;
	for (size_t i = 1; i < count; i++)
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

int play(char **map)
{
	size_t count;
	long *heaps;
	long *line_state;

	heaps = make_heaps(map, &count);
	if (!heaps)
		return (error_msg(ALLOC_ERR), 1);
	line_state = calc_line_state(heaps, count);
	if (!line_state)
		return (free(heaps), error_msg(ALLOC_ERR), 1);
	while (1)
	{
		if (draw(heaps, count, line_state))
			return (free(heaps), free(line_state), 1);
		if (solve_cur_map(heaps, &count, line_state))
			return (free(heaps), free(line_state), 1);
		if (check_heap(count, AI))
			return (free(heaps), free(line_state), 0);
		remove_empty_heap(heaps, &count);
		if (check_heap(count, AI))
			return (free(heaps), free(line_state), 0);
		if (draw(heaps, count, line_state))
			return (free(heaps), free(line_state), 1);
		if (take_input(heaps, &count))
			return (free(heaps), free(line_state), 1);
		if (check_heap(count, PLAYER))
			return (free(heaps), free(line_state), 0);
		remove_empty_heap(heaps, &count);
		if (check_heap(count, PLAYER))
			return (free(heaps), free(line_state), 0);
	}
}