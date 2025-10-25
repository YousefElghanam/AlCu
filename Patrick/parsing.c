
#include "alcu.h"
#include <stdlib.h>
#include <string.h>


static bool	check_datatyp(char *str)
{
	int		i;
	size_t	len;

	len = ft_strlen(str) - 4;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] == '.')
			return (false);
		i++;
	}
	if (!ft_strncmp(&str[len], ".map", 4))
		return (true);
	return (false);
}

static bool	number_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (false);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	input_check(char **map)
{
	size_t		i;
	size_t		num;

	i = 0;
	while (map[i])
	{
		if (!number_check(map[i]))
			return (false);
		num = ft_atoi(map[i]);
		if (num <= 0 || num > 10000)
			return (false);
		i++;
	}
	return (true);
}

bool	find_empty_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n' && str[i + 2] != '\0' )
			return (false);
		i++;
	}
	return (true);
}

char	**extract_map(char *map_path)
{
	char	line[BUFFER_SIZE];
	int		bytes;
	char	**map;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = read(fd, line, BUFFER_SIZE);
	if (bytes <= 0)
		return (close(fd), NULL);
	line[bytes] = '\0';
	map = ft_split(line, '\n');
	if (!map)
		return (close(fd), NULL);
	return (close(fd), map);
}


char *ft_line(int fd)
{
    char *line = (char *)malloc(BUFFER_SIZE + 1);
    int i = 0;
    char c;
    int bytes;

    if (!line)
        return NULL;
    while ((bytes = read(fd, &c, 1)) > 0)
    {
        if (c == '\n')
			break;
        if (i < BUFFER_SIZE)    // einfache Kapazitätsgrenze
            line[i++] = c;
        else
            break;
    }
    if (bytes <= 0 && i == 0)
	{
        free(line);
        return NULL;
    }
    line[i] = '\0';
    return line;
}

char **parse(int ac, char **av)
{
	char **map;	
	
	if (ac == 1)	//input ./alum1 < maps/map1.map
	{		
		map = calloc(10000, sizeof(char *));
		if (!map)
			return (NULL);
		char *line;
		int i = 0;

		while ((line = ft_line(0)) != NULL)
        {
            if (line[0] == '\0')
			{
				free(line);
				break;
			}
            map[i++] = line;
        }
	}
	else if (ac == 2) // input ./alum1 maps/map1.map
	{
		if (!check_datatyp(av[1]))
			return (write(2, "ERROR\n", 6), NULL);
		map = extract_map(av[1]);
		if (!map)
			return (NULL);
		if (VERBOSE)
			printf("valid map\n");
		//map = {"8", "5", "2", "1" NULL};
	}
	if (!input_check(map))
		return (write(2, "ERROR\n", 6), ft_freesplit(map), NULL);
	return (map);
}




