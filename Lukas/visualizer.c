/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:44:25 by lwittwer          #+#    #+#             */
/*   Updated: 2025/10/26 14:10:42 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_HEAPS 222
#define MAX_MATCHES 10
#define MAX_BARS 15

int	heaps[TOTAL_HEAPS];

void	init_heaps()
{
	int	i = -1;
	srand(time(NULL));
	while(++i < TOTAL_HEAPS)
	{
		heaps[i] = rand() % MAX_MATCHES + 1;
	}
}

int	main()//get char or int pointer
{
	initscr(); // starts ncurses
	noecho();	// dont show typed keys
	curs_set(FALSE);	//hide cursor
	keypad(stdscr, TRUE);
	nodelay(stdscr, FALSE);

	init_heaps();
	int	scroll = 0;
	int	ch;
	int	j;
	while (1)
	{
		clear();
		int max_y, max_x;
		getmaxyx(stdscr, max_y, max_x); // gets the height and width of the terminal -> updates if terminal size changes
		int i = -1;
		while (++i < max_y && (scroll + i) < TOTAL_HEAPS)
		{
			int	heap_index = scroll + i;
			int	heap_size = heaps[heap_index];
			mvprintw(i, 0, "Heap %4d: ", heap_index); //mvprint move the cursor to the xy position and prints multiple characters
			int bars = heap_size > MAX_BARS ? MAX_BARS : heap_size; // check with if for easier readability? dont like ter ops
			j = -1;
			while(++j < bars && (10 + j) < max_x - 6)
			{
				mvaddch(i, 10 + j, '|');
			}
			mvprintw(i, 10 + bars + 1, "(%d)", heap_size);
		}
		refresh(); // update window
		ch = getch();
		if (ch == 'q')
			break;
		else if (ch == KEY_UP)
		{
			if (scroll > 0)
				scroll--;
		}
		else if (ch == KEY_DOWN)
		{
			if (scroll < TOTAL_HEAPS - max_y)
				scroll++;
		}
	}
	endwin();
	return (0);
}
