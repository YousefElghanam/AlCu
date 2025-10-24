#include "alcu.h"

#define BUFFER_SIZE 100000

static bool	number_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (printf("ERROR: negativ numbers not allowed\n"), false);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (printf("ERROR: only numbers accepted\n"), false);
		i++;
	}
	return (true);
}

bool	input_check(char **av)
{
	size_t		i;
	long long	num;

	i = 1;
	while (av[i])
	{
		if (!number_check(av[i]))
			return (false);
		num = ft_atoi(av[i]);
		if (num <= 0 || num > INT_MAX)
			return (printf("ERROR: only pos numbers allowed\n"), false);
		i++;
	}
	return (true);
}

char **parse(int ac, char **av)
{
	
}