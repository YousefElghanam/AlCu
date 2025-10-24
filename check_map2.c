/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:15:57 by netrunner         #+#    #+#             */
/*   Updated: 2025/10/24 19:30:23 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



bool	find_empty_line(char *str)
{
	int		i;
	char	c;

	c = '1';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (false);
		i++;
	}
	return (true);
}

void	flood_fill(t_data *game, int x, int y)
{
	int	i;

	i = 0;
	if (x < 0 || y < 0 || x >= game->length.x || y >= game->length.y)
		return ;
	if (game->map[y][x] == '1' || game->map[y][x] == 'X')
		return ;
	else
	{
		game->map[y][x] = 'X';
		flood_fill(game, x + 1, y);
		flood_fill(game, x - 1, y);
		flood_fill(game, x, y + 1);
		flood_fill(game, x, y - 1);
	}
}

int	check_walls(char **map, t_data *game)
{
	int	i;

	i = 0;
	game->length.y = count_lines(map) - 1;
	while (map[i])
	{
		if (i == 0 || i == game->length.y)
		{
			if (ft_strcheck(map[i++], '1'))
				continue ;
			else
				return (0);
		}
		else
		{
			if (map[i][0] == '1' && map[i++][game->length.x] == '1')
				continue ;
			else
				return (0);
		}
	}
	return (1);
}

int	check_rectangular(char **map, size_t line_length)
{
	int	i;

	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i++]) == line_length)
			continue ;
		else
			return (0);
	}
	return (1);
}
