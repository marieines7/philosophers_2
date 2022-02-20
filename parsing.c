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
	{
		n = n * 10 + (s[i++] - '0');
	/*	if ((n > INT_MAX) || (n < INT_MIN))
		{
			printf("nb superieur a intmax ou inferieur a intmin");
			return(-1);
		}*/
	}
	return (sign * (int)n);
}


void	*ft_calloc(size_t count, size_t size)
{
	void	*s;
	size_t	i;

	s = (void *)malloc(count * size);
	i = 0;
	if (!s)
		return (NULL);
	while (i < count)
	{
		*(char *)(s + i) = 0;
		i++;
	}
	return (s);
}

/*
int    save_data(int ac, char **av, t_data **data)
{

//	t_data	*data;

//data = malloc(sizeof(*data));
//	data = malloc(sizeof(*data));
    data->one_philo_died = 0;
    data->nb_philosophers = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    if (data->nb_philosophers > 200)
    {
        printf ("Interdiction : trop de philosophers\n");
        return(-1);
    }
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->total_meals_for_each_philo = ft_atoi(av[5]);
	else
		data->total_meals_for_each_philo = INT_MAX;
    printf("\nnb_philo  %d, time die = %d, time eat = %d, time sleep %d, meals %d\n", data->nb_philosophers, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->total_meals_for_each_philo);
    if (data->nb_philosophers <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0 || data->total_meals_for_each_philo <= 0)
    {
        printf ("pas possible");
        return(-1);
    }
	if (data->nb_philosophers > INT_MAX || data->time_to_die > INT_MAX || data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX || data->total_meals_for_each_philo > INT_MAX)
    {
        printf ("pas possible bnt max");
        return(-1);
    }
	return (0);
}
*/


int    save_data(int ac, char **av, t_data *data)
{

//	t_data	*data;

//*data = malloc(sizeof(*data));
//	data = malloc(sizeof(*data));
    data->one_philo_died = 0;
    data->nb_philosophers = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    if (data->nb_philosophers > 200)
    {
        printf ("Interdiction : trop de philosophers\n");
        return(-1);
    }
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->total_meals_for_each_philo = ft_atoi(av[5]);
		data->option = 1;
	}
	else
		data->option = 0;
    printf("\nnb_philo  %d, time die = %d, time eat = %d, time sleep %d, meals %d\n", data->nb_philosophers, data->time_to_die, data->time_to_eat, data->time_to_sleep, data->total_meals_for_each_philo);
    if (data->nb_philosophers <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0 || data->total_meals_for_each_philo <= 0)
    {
        printf ("pas possible");
        return(-1);
    }
	if (data->nb_philosophers > INT_MAX || data->time_to_die > INT_MAX || data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX || data->total_meals_for_each_philo > INT_MAX)
    {
        printf ("pas possible bnt max");
        return(-1);
    }
	return (0);
}

int	get_right_args(int ac, char **av)
{
	if ((ac != 5) && (ac != 6))	
	{
		printf("invalid nb of args. number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat\n");
		return(0);
	}	
//	else if (ac == 5) // a enlever
//		return(printf("ok nb args\n"));
	if (!all_are_digits(av))
	{
		printf("invalid arg, not a number\n");
		return(0);
	}
	return(1);
}

