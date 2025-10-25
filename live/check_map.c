/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:15:57 by netrunner         #+#    #+#             */
/*   Updated: 2025/08/31 14:42:35 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

char	**extract_map(char *map_path)
{
	char	*line;
	int		bytes;
	char	**map;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!line)
		return (close(fd), NULL);
	bytes = read(fd, line, BUFFER_SIZE);
	if (bytes <= 0)
		return (close(fd), free(line), NULL);
	line[bytes] = '\0';
	if (!find_empty_line(line))
		return (close (fd), free(line), NULL);
	map = ft_split(line, '\n');
	if (!map)
		return (close(fd), free(line), NULL);
	return (close(fd), free(line), map);
}

bool	check_doubles(t_data *game)
{
	int		i;
	t_bool	_bool;

	_bool = (t_bool){0};
	i = 0;
	while (game->map[i])
	{
		if (find_char(game->map[i], 'P'))
		{
			if (!_bool.player && count_letters(game->map[i], 'P') == 1)
				_bool.player = true;
			else
				return (false);
		}
		if (find_char(game->map[i], 'E'))
		{
			if (!_bool.exit && count_letters(game->map[i], 'E') == 1)
				_bool.exit = true;
			else
				return (false);
		}
		i++;
	}
	return (true);
}

void	set_coords(bool *env, t_coord *point, int y, int x)
{
	(*point).x = x;
	(*point).y = y;
	*env = true;
}

int	check_letters_on_map(t_data *game)
{
	t_bool	_bo;
	int		i;

	_bo = (t_bool){0};
	i = 0;
	while (game->map[i])
	{
		if (find_char(game->map[i], 'P'))
			set_coords(&_bo.player, &game->player, i,
				find_char(game->map[i], 'P'));
		if (find_char(game->map[i], 'C'))
		{
			game->coin_count += count_letters(game->map[i], 'C');
			_bo.coins = true;
		}
		if (find_char(game->map[i], 'E'))
			set_coords(&_bo.exit, &game->exit, i, find_char(game->map[i], 'E'));
		i++;
	}
	if (_bo.player == true && _bo.exit == true && _bo.coins == true)
		return (1);
	else if (_bo.player == false && _bo.exit == false && _bo.coins == false)
		return (0);
	return (-1);
}

bool	check_forbidden_chars(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1' ||
				game->map[y][x] == 'C' ||
				game->map[y][x] == 'P' ||
				game->map[y][x] == '0' ||
				game->map[y][x] == 'E')
			{
				x++;
				continue ;
			}
			else
				return (false);
		}
		y++;
	}
	return (true);
}
