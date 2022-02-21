#include "philo.h"


//parsing
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
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (s[i++] - '0');
	return (sign * (int)n);
}

int	right_args(int ac, char **av)
{
	int j;

	j = 0;
	if ((ac != 5) && (ac != 6))
	{
		printf("invalid nb of args. number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat\n");
		return (0);
	}
	while(av[++j])
	{
		if (ft_atoi(av[1]) > 200 || ft_atoi(av[j]) <= 0 || ft_atoi(av[j]) > INT_MAX)
		{
			printf("too big of a value or a negative value. not possible. for your info no more than 200 philos are possible\n");
			return (0);
		}	
	}
	if (!all_are_digits(av))
	{
		printf("stray character that aka not all are positive numbers\n");
		return (0);
	}
	return(1);
}

int    save_data(int ac, char **av, t_data *data)
{
    data->nb_philosophers = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->total_meals_for_each_philo = ft_atoi(av[5]);
		data->option = 1;
	}
	else
	{
		data->option = 0;
	}
		
    printf("\nnb_philo  %d, time die = %ld, time eat = %d, time sleep %d, meals %d\n", data->nb_philosophers, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->total_meals_for_each_philo);
	return (0);
}