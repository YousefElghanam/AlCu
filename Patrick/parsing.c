
#include "alcu.h"

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
			return (printf("numbercheck\n"), false);
		num = ft_atoi(map[i]);
		if (num <= 0 || num > 10000)
			return (printf("0 or biggger than 10000\n"),false);
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
	if (!find_empty_line(line))
		return (close (fd), NULL);
	map = ft_split(line, '\n');
	if (!map)
		return (close(fd), NULL);
	return (close(fd), map);
}

char *line(int fd)
{

	static char	buf[BUFFER_SIZE];
	static int	i = 0, bytes= 0;
	char	*line;
	int	j = 0;
	if (!(line = calloc(10000, 1)))
		return (NULL);
	while (1)
	{
		if (i >= bytes)
		{
			i = 0;
			bytes= read(fd, buf, BUFFER_SIZE);
			if (bytes <= 0)
			{
				if (bytes < 0)
					return (free(line), perror("Error"), NULL);
				break ;
			}
		}
		line[j++] = buf[i++];
		if (line[j - 1] == '\n')
			break ;
	}
	if (j)
	{
		line[j] = '\0';
		printf("%s", line);
		return (line);
	}
	else
	{
		free(line);
		line = NULL;
		i = 0;
		bytes = 0;
		return (NULL);
	}
}

char **parse(int ac, char **av)
{
	char **map = NULL;

	if (ac == 1)
	{
		char buffer[BUFFER_SIZE];
		int bytes = 0;
		while (1)
		{
			bytes = read(0, buffer, BUFFER_SIZE);
			if (bytes <= 0)
			{
				if (bytes < 0)
					return (NULL);
				break ;
			}
			buffer[bytes] = '\0';
			if (buffer[0] == '\n')
				break ;
		}
		printf("%s", buffer);
		return (ft_split(buffer, '\n'));
	}
	else if (ac == 2) // input ./alum1 maps/map1.map
	{
		map = extract_map(av[1]);
		if (!map)
			return (NULL);
		if (!input_check(map))
			return (write(2, "ERROR\n", 6), NULL);
		if (VERBOSE)
			printf("valid map\n");
		//map = {"8", "5", "2", "1" NULL};
	}

	return (map);
}




