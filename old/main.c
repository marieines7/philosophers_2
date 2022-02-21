#include "philo.h"
void philo_life(t_philo *philo, int i)
{
  /*  t_data *data;

    data = philo->data;
	*/
	pthread_mutex_lock(philo[i]->left_fork);
	print_activity(philo[i], "has taken a fork");
	pthread_mutex_lock(pphilo[i]->left_fork);
	print_activity(philo[i], "has taken a fork");
    //is eating
	pthread_mutex_lock(&philo[i]->is_eating);
	philo->last_meal = current_timestamp(); //ou gettimeofday(&philo->last_eat, NULL); //philo->last_meal = current_timestamp(data->start_time);
	pthread_mutex_unlock(&philo[i]->is_eating);
	print_activity(philo[i], "is eating");
	timer(philo[i]->time_to_eat);

    pthread_mutex_lock(&philo[i]->is_eating);
    philo[i]->total_meals++;
    pthread_mutex_unlock(&philo[i]->is_eating);

	pthread_mutex_unlock(philo[i]->left_fork);
	pthread_mutex_unlock(philo[i]->right_fork);

    //is sleeping
	print_activity((&philo[i], "is sleeping");
	timer(data->time_to_sleep);
	//is thinking
    print_activity((&philo[i], "is thinking");
}


int one_philo_died(t_philo *philo)
{
    //t_data *data;

    //data = philo->data;
	printf("\nMy philo is %i\n", philo->id);
	printf("current timestamp: %lu\n", current_timestamp());
	printf("last_meal: %lu\n", philo->last_meal);
	printf("time_to_die: %lu\n", philo->data->time_to_die);
	/*
    if ((unsigned int)(current_timestamp() - philo->last_meal) > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_activity);
        printf("%ldms %d is dead\n", current_timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_activity);
        return(1);
    }
	*/
    return(0);
}

int end_simulation(t_philo *philo)
{
    unsigned int    i;
    int            all_had_enough_to_eat;
   
    i = -1;
   // one_died = 0;
    all_had_enough_to_eat = 1;
    while (++i < philo[i]->nb_philosophers)
    {
        pthread_mutex_lock(&philo[i]->eating);
        if (philo[i].total_meals < philo[i]->total_meals_for_each_philo)
            all_had_enough_to_eat = 0;
        pthread_mutex_unlock(&philo[i]->eating);
		if (one_philo_died(&philo[i]) == 1)
            break;
    }
  //  pthread_mutex_lock(&data->end_simulation);
    if ( (data->option == 0 && (data->one_philo_died == 1)) 
	|| (data->option == 1 && (data->total_meals_for_each_philo != -1) && (all_had_enough_to_eat == 1)))
        return(1);
   // pthread_mutex_unlock(&data->end_simulation);
	
    return (0);
}


void *simulation(void *arg)
{
    int     death;

	(void)death;
	t_philo *philo;
	
	philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->end_simulation);
    death = end_simulation(data);
	printf("je passe dans end simulation\n");
    pthread_mutex_unlock(&data->end_simulation);
	printf("coucou ca va mieux\n");
/*    while (death == 0)
    {
        philo_life(data->philo);
        pthread_mutex_lock(&data->end_simulation);
        //death = end_simulation(philo);
        death = end_simulation(data->philo);
        pthread_mutex_unlock(&data->end_simulation);
    }
*/
//	printf("simulation philo\n");
	return(0);
}


/*
//version 2
void *simulation(void *arg)
{

    int one_philo_died;
    t_philo *philo;
    t_data *data;

    one_philo_died = 0;
    philo = (t_philo *)arg;
    data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->end_simulation);
		one_philo_died = end_simulation(philo);
		pthread_mutex_unlock(&data->end_simulation);
		if (one_philo_died == 1)
			break;
		philo_life(philo);
	}
	return(0);
}
*/
void	do_activities_stimultanously(t_data *data)
{
	unsigned int	i;

	i = 0;	t_philo *philo;

	philo = data->philo;

	while (i < data->nb_philosophers)
	{
		if ((i % 2) == 0)
			pthread_create(&data->philo_lives[i], NULL, &simulation, (void *)philo);
		else if ((i % 2) == 1)
		{
			timer(300);
			pthread_create(&data->philo_lives[i], NULL, &simulation,  (void *)philo);
		}
       		 i++;
	}
	i = 0;
	while (++i <= data->nb_philosophers)
		pthread_join(data->philo_lives[i], NULL);
}

void	share_left_fork_with_right_neighbour(t_philo *philo)
{
	unsigned int	i;
	pthread_mutex_t fork[200];
	pthread_mutex_t is_eating[200];

	i = 0;
	if (philo[i].nb_philosophers > 1)
	{
		while (i < philo[i].nb_philosophers)
		{
				printf("ok\n");
				pthread_mutex_init(&fork[i], NULL);
				pthread_mutex_init(&is_eating[i], NULL);
				philo[i].left_fork = &fork[i];
				i++;
		}
	}
	i = 0;
	if (philo[i].nb_philosophers > 1)
	{
		while (++i < philo[i].nb_philosophers)
			philo[i].right_fork = philo[(i + 1) % philo[i].nb_philosophers].left_fork;
	}
}




void	init_philos(t_philo *philo, char **av, int nb_meals_option)
{
	t_philo philo[200];
	unsigned int     i;

	i = -1;
	//printf("je passe dans init philo");
	printf("nb de philos = %d\n", data->nb_philosophers);
	while (++i < philo[i]->nb_philosophers)
	{
		printf("je passe dans add philo\n");
	 	philo[i].id = i + 1;
	 	philo[i].total_meals = 0;
		philo[i].last_meal = 0;
    	philo[i].nb_philosophers = ft_atoi(av[1]);
   		philo[i].time_to_die = ft_atoi(av[2]);
   		philo[i].time_to_eat = ft_atoi(av[3]);
   	 	philo[i].time_to_sleep = ft_atoi(av[4]);
		philo[i].total_meals_for_each_philo = ft_atoi(av[5]);
		philo[i].option = nb_meals_option;
	}
	share_left_fork_with_right_neighbour(philo);
}


void init_mutexes()
{
	pthread_mutex_init(&data.print_activity, NULL);
	pthread_mutex_init(&data.end_simulation, NULL);
	pthread_mutex_init(&data.eating, NULL);
}




void one_philo(t_philo *philo)
{
	int i;

    print_activity(philo->philo[i], "has taken a fork\n");
    timer(philo[i]->time_to_die);
    print_activity(philo->philo[i], "is dead\n");
}

int main(int ac, char **av)
{
	int option;
	t_philo philo[200];
	option = 1;
	if (ac == 1)
        return(printf("nb arguments\n"));
	if(!right_args(ac, av))
        return(0);

/*
	if (ac == 6)
		option = 1;
	printf("init mutexes...\n");
	init_mutexes();
	printf("init philos...\n");
//	init_philos(&philo, av, option);
	data.start_time = current_timestamp();
	printf("data start time = %ld\n", data.start_time);

    printf("check init... : \n");
	while(++i < philo[i].nb_philosophers)
        	printf("\nphilo id = %d, total meal = %d, last meal = %d", philo[i].id, philo[i].total_meals, philo[i].last_meal);


	if (philo[i].nb_philosophers == 1)
		one_philo(&data);
	else
		do_activities_stimultanously(&data);
  //free_all(data);
	*/
	return (0);
}