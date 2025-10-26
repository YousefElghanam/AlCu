#include "alcu.h"
#include <time.h>
#include <ncurses.h>

size_t	y_offset = 0;
size_t	bars_global = 0;
int		var = 0;
void	print_heap_goal(long *line_state, size_t x)
{
	if (line_state[x] == 0)
		ft_printf(1, "[LOSE]	");
	else
		ft_printf(1, "[WIN ]	");
}
#define MAX_MATCHES 100
#define MAX_BARS 50

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
		i += 19;
	}
}

int move_to_lose_line(long items)
{
	if (items == 1 || items == 2 || items == 3)
		return (items);
	else if (items % 4 == 1)
		return (1);
	else if (items % 4 == 2)
		return (2);
	else if (items % 4 == 3)
		return (3);
	else if (items % 2 == 0 && items >= 2)
		return (2);
	else
		return (1);
}

int move_to_win_line(long items)
{
	if ((items % 4) == 3)
		return (2);
	else if (items % 4 == 0)
		return (3);
	else if (items % 2 == 1 && items >= 2)
		return (2);
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
	// think();
	int moves = 1;

	moves = calc_moves(heaps, *count, line_state);
	heaps[*count - 1] -= moves;
	// mvprintw(y_offset, 0, "AI takes %d\n", moves);
	y_offset++;
	ft_putstr_fd("AI takes ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putchar_fd('\n', 1);
	refresh();
	return (0);
}

int take_input(long *heaps, size_t *count)
{
	char input[10001];
	long input_int;
	ssize_t bytes_read;
	while (1)
	{
		y_offset++;
		// mvprintw(y_offset, 0, "Player input: ");
		ft_putstr_fd("Player input: ", 1);
		ft_memset(input, 0, 10001);
		bytes_read = read(1, input, 10000);
		if (bytes_read == -1)
			return (error_msg(READ_ERR), refresh(), 1);
		if (bytes_read == 0)
			// return (mvprintw(y_offset, 0, "Player quits, AI wins\n"), y_offset++, 1);
			return (ft_putstr_fd("Player quits, AI wins\n", 1), refresh(), 1);
		input[bytes_read] = 0;
		input_int = ft_atoi_but_better(input);
		if (input_int == 2147483648 || input_int < 1 || input_int > 3)
		{
			mvprintw(y_offset, 0, "Invalid input, please enter a number between 1 and 3\n");
			// y_offset++;
			refresh();
			// ft_putendl_fd("Invalid input, please enter a number between 1 and 3", 1);
			continue;
		}
		if (input_int > heaps[*count - 1])
		{
			// mvprintw(y_offset, 0, "Not enough items in heap,\nplease enter a number between 1 and 3\n");
			// y_offset++;
			ft_putendl_fd("Not enough heaps in heap,\nplease enter a number between 1 and 3", 1);
			refresh();
			continue;
		}
		heaps[*count - 1] -= input_int;
		if (heaps[*count - 1] == 0 && *count > 1)
		{
			heaps[*count - 1] = -1;
			*count -= 1;
		}
		if (*count == 1 && heaps[1] == 1)
		// mvprintw(y_offset, 0, "\nYou win!\n");
		// y_offset++;		
		// ft_putendl_fd("\nYou win!", 1);
		var = 1;
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
		// return (mvprintw(y_offset, 0, "\nYou lose!\n"), y_offset++, 1);
		return (var = 2, 1);
	else if (count == 0 && !is_player)
		// return (mvprintw(y_offset, 0, "\nYou win!\n"), y_offset++, 1);
		return (var = 1, 1);
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

int	draw_heaps(long *heaps, size_t count)
{
	size_t	scroll = 0;
		size_t	j;
		size_t max_y, max_x;
		getmaxyx(stdscr, max_y, max_x); // gets the height and width of the terminal -> updates if terminal size changes
		y_offset = 0;
		bars_global = 0;
		// size_t heap_size_global = 0;
		clear();
		while (y_offset < max_y / 2 && (scroll + y_offset) < count)
		{
			size_t	heap_index = scroll + y_offset;
			size_t	heap_size = heaps[heap_index];
			mvprintw(y_offset, 0, "Heap %4zu: ", heap_index); //mvprint move the cursor to the xy position and prints multiple characters
			size_t bars = heap_size > MAX_BARS ? MAX_BARS : heap_size; // check with if for easier readability? dont like ter ops
			j = 0;
			while(j < bars && (10 + j) < max_x / 2 - 6)
			{
				mvaddch(y_offset, 10 + j, '|');
				j++;
			}
			mvprintw(y_offset, 10 + bars + 1, "(%zu)", heap_size);
			y_offset++;
			bars_global = bars;
			// heap_size_global = heap_size;
		}
		mvprintw(y_offset, 10 + bars_global + 1, "\n");
		refresh();
		// y_offset++;
		return (0);
}

int draw(long *heaps, size_t count, long *line_state)
{
	WINDOW *win;

	win = initscr(); // starts ncurses
	noecho();	// dont show typed keys
	// curs_set(FALSE);	//hide cursor
	keypad(win, TRUE);
	nodelay(win, FALSE);
	
	(void)line_state;
	// int	ch;
	while (1)
	{
		draw_heaps(heaps, count);
		// clear();
		
		// update window		// if (draw(heaps, count, line_state))
		// 	return (free(heaps), free(line_state), 1);
			// usleep(1000000);
			// refresh();
			if (solve_cur_map(heaps, &count, line_state))
				return (endwin(), free(heaps), free(line_state), 1);
			// usleep(1000000);
			refresh();
			// usleep(1000000);
			if (check_heap(count, AI))
				return (endwin(), free(heaps), free(line_state), 0);
			// usleep(1000000);
			remove_empty_heap(heaps, &count);
			draw_heaps(heaps, count);
			if (check_heap(count, AI))
				return (endwin(), free(heaps), free(line_state), 0);
			// usleep(1000000);
			refresh();
		// refresh();
		// clear();
			// 	return (free(heaps), free(line_state), 1);

		// refresh();
			// refresh();
			//mvprintw(y_offset, 10 + bars_global + 1, "\n");
			// usleep(1000000);
			// ft_putstr_fd("Player input: ", 1);
			if (take_input(heaps, &count))
				return (endwin(), free(heaps), free(line_state), 1);
			refresh();
			// usleep(1000000);
			if (check_heap(count, PLAYER))
				return (endwin(), free(heaps), free(line_state), 0);
			// usleep(1000000);
			remove_empty_heap(heaps, &count);
			draw_heaps(heaps, count);
			if (check_heap(count, PLAYER))
				return (endwin(), free(heaps), free(line_state), 0);
				// usleep(1000000);
			//refresh();
		// ch = getch();
		// if (ch == 'q')
		// 	break;
		// else if (ch == KEY_UP)
		// {
		// 	if (scroll > 0)
		// 		scroll--;
		// }
		// else if (ch == KEY_DOWN)
		// {
		// 	if (scroll < count - max_y)
		// 		scroll++;
		// }
	}
	endwin();
	return (0);
	// long i;

	// for (size_t x = 0; x < count; x++)
	// {
	// 	if (count == SIZE_MAX)
	// 		break;
	// 	i = 0;
	// 	if (VERBOSE)
	// 		print_heap_goal(line_state, x);
	// 	ft_putchar_fd('[', 1);
	// 	ft_putnbr_fd(heaps[x], 1);
	// 	ft_putstr_fd("]	: ", 1);
	// 	while (i++ < heaps[x])
	// 		ft_putstr_fd("| ", 1);	
	// 	ft_putchar_fd('\n', 1);
	// }
	// ft_putchar_fd('\n', 1);
	// return (0);
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
	if (draw(heaps, count, line_state))
		return (1);
	if (var == 2)
		printf("You lose\n");
	else if (var == 1)
		printf("You win\n");
	return (0);
}