

/*
tests:

no death/infinite loop
5 800 200 200
4 410 200 200

no death/7 meals then stop
5 800 200 200 7

One death
1 800 200 200
4 310 200 100


*/
// .h
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <pthread.h>


typedef struct  s_philo
{
	int id;
	pthread_t philo_life;
	pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
	int state;
	unsigned long last_meal;
	unsigned int total_meals;
	struct  s_data *data;
}   t_philo;

typedef struct  s_data
{
	t_philo *philo;
	pthread_mutex_t eating; //forks
	pthread_mutex_t end_simulation;//monitor. pthread_t ou pthread_mutex??
	pthread_mutex_t print_activity;
	pthread_mutex_t *forks;
	unsigned long start_time;
	unsigned int nb_philosophers;
	unsigned long time_to_die;
	int time_to_eat;
	int time_to_sleep;
	unsigned int total_meals_for_each_philo;
	int	one_philo_died;
	int option;
	int total_meals; //meal count
}   t_data;


//utils

long int current_timestamp(void)
{
    long int time;
    struct timeval current_time;

    time = 0;
    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return (time);
}

void timer(int activity_duration)
{
    long int start_time;
    long int current_time;

    start_time = current_timestamp();
    current_time = start_time;
    while ((current_time - start_time) < activity_duration)
    {
       usleep(100);
       current_time = current_timestamp();
    }
}


void    print_activity(t_philo *philo, char *activity)
{
    pthread_mutex_lock(&philo->data->end_simulation);
    if (philo->data->one_philo_died == 1)
       return ;
    pthread_mutex_unlock(&philo->data->end_simulation);
    pthread_mutex_lock(&philo->data->print_activity); 
    printf("%ldms:  philosopher %d   %s\n", current_timestamp() - philo->data->start_time, philo->id, activity); // checker pour le +1 philo id
    pthread_mutex_unlock(&philo->data->print_activity);
}
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



int	init_philos(t_data *data)
{
	unsigned int	i;

	i = -1;
	while (++i < data->nb_philosophers)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0; //get ms??init file
		data->philo[i].total_meals = 0; //get ms??init file
		if(pthread_mutex_init(&data->philo[i].left_fork, NULL) != 0) /// & a remettre ?
		{
			printf("error init left fork de %d\n", data->philo[i].id);
			return(0);
		}
		data->philo[i].data = data;
	}
	i = -1;
	while (++i < data->nb_philosophers)
		data->philo[i].right_fork = data->philo[(i + 1) % data->nb_philosophers].left_fork; //&left_fork a remettre?
	return (1);
}

void philo_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_activity(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork);
	print_activity(philo, "has taken a fork");
 //is eating
	pthread_mutex_lock(&philo->data->eating);
	philo->last_meal = current_timestamp(); //ou gettimeofday(&philo->last_eat, NULL); //philo->last_meal = current_timestamp(data->start_time);
	philo->total_meals++;
	printf("total mels %d\n", philo->total_meals);
	pthread_mutex_unlock(&philo->data->eating);
	print_activity(philo, "is eating");
	timer(philo->data->time_to_eat);

	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);

    //is sleeping
	print_activity(philo, "is sleeping");
	timer(philo->data->time_to_sleep);
	//is thinking
    print_activity(philo, "is thinking");
	

}

int one_philo_died(t_philo *philo)
{
    if ((current_timestamp() - philo->last_meal) > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_activity);
        printf("%ldms philo %d is dead\n", current_timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_activity);
        return(1);
    }
    return(0);
}

int end_simulation(t_philo *philo)
{
    unsigned int    i;
    unsigned int             all_had_enough_to_eat;
   // int             one_died;

    i = 0;
   // one_died = 0;
    all_had_enough_to_eat = 1;
    while (i < philo->data->nb_philosophers)
    {
        pthread_mutex_lock(&philo->data->eating);
        if (philo->total_meals < philo->data->total_meals_for_each_philo)
            all_had_enough_to_eat = 0;
        pthread_mutex_unlock(&philo->data->eating);
	if (one_philo_died(philo))
        {
            philo->data->one_philo_died = 1;
            break;
        }
        i++;
    }
    pthread_mutex_lock(&philo->data->end_simulation);
    if ((philo->data->one_philo_died == 1) ||
	((philo->data->option == 1) && ((int)philo->data->total_meals_for_each_philo != -1) && (all_had_enough_to_eat == 1)))
        return(1);
    pthread_mutex_unlock(&philo->data->end_simulation);
    return (0);
}

void *simulation(void *arg)
{
    t_philo *philo;
  // int     death;

    philo = (t_philo *)arg;
	printf("je passe dans simulation. philo %d total meals eaten = %d; total meals to eat = %d\n", philo->id, philo->total_meals, philo->data->total_meals_for_each_philo);
//	printf("philo %d has eaten %d meals", philo->id, philo->total_meals);
	while ((philo->data->option == 1 && (philo->total_meals < philo->data->total_meals_for_each_philo)))
	{
		philo_life(philo);
	}
   /* pthread_mutex_lock(&philo->data->end_simulation);
    death = end_simulation(philo->data->philo);
    pthread_mutex_unlock(&philo->data->end_simulation);
    while (death == 0)
    {
        philo_life(philo);
        pthread_mutex_lock(&philo->data->end_simulation);
        //death = end_simulation(philo);
        death = end_simulation(philo);
        pthread_mutex_unlock(&philo->data->end_simulation);
    }
	
	//printf("philo %d: ok je suis en train de vivre\n", philo->id);
*/	return(0);
}
/*
void *simulation(void *arg)
{
	t_philo *philo;
	unsigned int i;
    int one_philo_died
	philo = (t_philo *)arg;
	i = -1;
	while (++i < philo->data->nb_philosophers)
	{
		if (one_philo_died == 1)
			return(0);
		philo_life();
	}
	return (0);
}
*/
int	do_activities_stimultanously(t_data *data)
{
	unsigned int	i;

	i = -1;
	while (++i < data->nb_philosophers)
	{
		if ((i % 2) == 0)
		{
			if (pthread_create(&data->philo[i].philo_life, NULL, &simulation, &data->philo[i]) != 0)
			{
				printf("error creating philo life\n");
				return(0);
			}
				
		}
	}
	i = -1;
	while (++i < data->nb_philosophers)
	{
		if ((i % 2) == 1)
		{
			usleep(100);
			if (pthread_create(&data->philo[i].philo_life, NULL, &simulation, &data->philo[i]) != 0)
			{
				printf("error creating philo life\n");
				return(0);
			}
		}
	}
	i = -1;
	while (++i < data->nb_philosophers)
	{
	/*	printf("is is %i\n", i);
		printf("is ok ? data %p\n", data);
		printf("is ok ? data->philo %p\n", data->philo);
		printf("is ok ? data->philo[i] %p\n", &data->philo[i]);
		printf("is ok ? data->philo[i]->philo_life %p\n", &(data->philo[i].philo_life));
	*/	 
		 
		pthread_join(data->philo[i].philo_life, NULL);
/*
		printf("coucou toii %d\n", i);
		if (pthread_join(data->philo[i].philo_life, NULL) != 0)
		{
				printf("error doing stuff stimultanously\n");
				return(0);
		}
*/	}
	printf("fin game\n");	
	return(0);
}


void one_philo(t_philo *philo)
{
    print_activity(philo, "has taken a fork\n");
    timer(philo->data->time_to_die);
    print_activity(philo, "is dead\n");
}

void free_all(t_data * data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	pthread_mutex_destroy(&data->print_activity);
	pthread_mutex_destroy(&data->end_simulation);
	pthread_mutex_destroy(&data->eating);
}

int init_simulation(t_data *data)
{
	unsigned int i;

	data->philo = malloc(data->nb_philosophers * sizeof(t_philo));
	if(!data->philo)
		return (0);
	data->forks = malloc(data->nb_philosophers * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	data->start_time = current_timestamp();
	printf("deja init les forks etc je vais init philos\n");

	if (!init_philos(data))
		return (-1);

	if (data->nb_philosophers == 1)
	{
		one_philo(data->philo);
		free_all(data);
		return(1);
	}
	i = -1;
	if (do_activities_stimultanously(data))
	{
		i = -1;
		while (++i < data->nb_philosophers)
			pthread_mutex_destroy(&data->forks[i]);
		free_all(data);
		return(0);
	}
		return (-1);
	//pthread_join(data->end_simulation, NULL); // a rechecker
	printf("je passe par la\n");
	return (1);
}


int main(int ac, char **av)
{
	t_data data;
	if(!right_args(ac, av))
		return(0);
	save_data(ac, av, &data);

	if (pthread_mutex_init(&data.print_activity, NULL) != 0)
	{
		printf("error init print\n");
		return(0);
	}
	
	if (pthread_mutex_init(&data.end_simulation, NULL) != 0)
	{
		printf("error end simulation\n");
		return(0);
	}
	if (pthread_mutex_init(&data.eating, NULL) != 0)
	{
		printf("error init print\n");
		return(0);
	}
	if(!init_simulation(&data))
		return(0);
}
