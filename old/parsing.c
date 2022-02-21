#include "philo.h"

int all_are_digits(char **s)
{
    int i;
    int j;

    j = 0;
    while(s[++j])
    {
        i = -1;
        while(s[j][++i])
        {
            if (!(s[j][i] >= '0' && s[j][i] <= '9'))
                return(0);
        }
    }
    return(1);
}

int ft_atoi(char *s)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && ((s[i] == '+') || (s[i] == '-')))
	{
		if (s[i++] == '-')
			sign = sign * -1;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (s[i++] - '0');
	return (sign * (int)n);
}

int	right_args(int ac, char **av)
{
	int j;

	j = 0;
	if ((ac != 5) && (ac != 6))	
		return (printf("invalid nb of args. number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat\n"));
	if (!all_are_digits(av))
		return(printf("invalid arg, not a number\n"));
	while(av[++j])
	{
		if (ft_atoi(av[1]) > 200)
			return (printf("pas possible\n"));
		if (ft_atoi(av[j]) <= 0 || ft_atoi(av[j]) > INT_MAX)
			return (printf("pas possible int max\n"));
	}
	return(0);
}

