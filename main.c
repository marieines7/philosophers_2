#include "philo.h"
void philo_life(t_philo *philo)
{
    t_data *data;

    data = philo->data;
	pthread_mutex_lock(philo->left_fork);
	print_activity(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_activity(philo, "has taken a fork");

    //is eating
	pthread_mutex_lock(&data->eating);
	philo->last_meal = current_timestamp(); //ou gettimeofday(&philo->last_eat, NULL); //philo->last_meal = current_timestamp(data->start_time);
	pthread_mutex_unlock(&data->eating);
	print_activity(philo, "is eating");
	timer(data->time_to_eat);

    pthread_mutex_lock(&data->eating);
    philo->total_meals++;
    pthread_mutex_unlock(&data->eating);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

    //is sleeping
	print_activity(philo, "is sleeping");
	timer(data->time_to_sleep);
	//is thinking
    print_activity(philo, "is thinking");
}


int one_philo_died(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    if ((current_timestamp() - philo->last_meal) > data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_activity);
        printf("%ldms %d is dead\n", current_timestamp(), philo->id);
        pthread_mutex_unlock(&philo->data->print_activity);
        return(1);
    }
    return(0);
}

int end_simulation(t_philo *philo)
{
    unsigned int    i;
    int             all_had_enough_to_eat;
    int             one_died;
    t_data *data;

    data = philo->data;

    i = 0;
    one_died = 0;
    all_had_enough_to_eat = 1;
    while (i < philo->data->nb_philosophers)
    {
        pthread_mutex_lock(&data->eating);
        if (philo[i].total_meals < data->total_meals_for_each_philo)
            all_had_enough_to_eat = 0;
        pthread_mutex_unlock(&data->eating);
       
	if (one_philo_died(&philo[i]))
        {
            data->one_philo_died = 1;
            break;
        }
        i++;
    }
    pthread_mutex_lock(&data->end_simulation);
    if ( (data->option == 0 && (data->one_philo_died == 1)) 
	|| (data->option == 1 && (data->total_meals_for_each_philo != -1) && (all_had_enough_to_eat == 1)))
        return(1);
    pthread_mutex_unlock(&data->end_simulation);
    return (0);
}


//v1
void *simulation(void *arg)
{
//    t_philo *philo;
    t_data *data;
    int     death;

    //data = philo->data;
  //  philo = (t_philo *)arg;
	data = (t_data *)arg;
    pthread_mutex_lock(&data->end_simulation);
    //death = end_simulation(philo);
    death = end_simulation(data->philo);
    pthread_mutex_unlock(&data->end_simulation);
    while (death == 0)
    {
        philo_life(data->philo);
        pthread_mutex_lock(&data->end_simulation);
        //death = end_simulation(philo);
        death = end_simulation(data->philo);
        pthread_mutex_unlock(&data->end_simulation);
    }
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
	int	i;

	i = 0;
/*	t_philo *philo;

	philo = data->philo;
*/
	while (i < data->nb_philosophers)
	{
		if ((i % 2) == 0)
			pthread_create(&data->philo_lives[i], NULL, &simulation, &data->philo[i]);
		else if ((i % 2) == 1)
		{
			timer(300);
			pthread_create(&data->philo_lives[i], NULL, &simulation, &data->philo[i]);
		}
       		 i++;
	}
	i = 0;
	while (++i <= data->nb_philosophers)
		pthread_join(data->philo_lives[i], NULL);
}

void	share_left_fork_with_right_neighbour(t_philo *philo, t_data *data)
{
	unsigned int	i;
	//t_data	*data;

	//data = philo->data;
	i = -1;
	pthread_mutex_t fork[200];
//	pthread_mutex_t is_eating[200];
	if (data->nb_philosophers > 1)
	{
		while (++i < data->nb_philosophers)
		{
				printf("ok\n");
				pthread_mutex_init(&fork[i], NULL);
			//	pthread_mutex_init(&is_eating[i], NULL);
				data->philo[i].left_fork = &fork[i];
		}
	}
	i = -1;
	if (data->nb_philosophers > 1)
	{
		while (++i < data->nb_philosophers)
			data->philo[i].right_fork = data->philo[(i + 1) % data->nb_philosophers].left_fork;
	}
}


void	init_philos(t_data *data)
{
	unsigned int     i;
	i = 0;
printf("je passe dans init philo");
	printf("nb de philos = %d\n", data->nb_philosophers);
	while (i < data->nb_philosophers)
	{
		printf("je passe dans add philo\n");
		data->philo[i].id = i + 1;
		data->philo[i].total_meals = 0;
		data->philo[i].last_meal = 0;
	//	data->philo[i].left_fork = NULL;
		data->philo[i].right_fork = NULL;
		//add_philo(philo, i);
		i++;
	}
	share_left_fork_with_right_neighbour(data->philo, data);
}

#include <string.h>
int main(int ac, char **av)
{
//	t_philo *philo;
	//t_data *data;
	t_data data;
//data = malloc(sizeof(*data));
    if (ac == 1)
        return(printf("nb arguments\n"));
	if(!get_right_args(ac, av))
        return(0);
	if (save_data(ac, av, &data) == -1)
        return (0);
	pthread_mutex_init(&data.print_activity, NULL);
    pthread_mutex_init(&data.end_simulation, NULL);
    pthread_mutex_init(&data.eating, NULL);
  
    printf("init philos...\n");
    init_philos(&data);
    data.start_time = current_timestamp();
    printf("data start time = %ld\n", data.start_time);
	unsigned int i = -1;
    printf("check init... : \n");
/*    t_philo *philo = data.philo;
	while(++i < data.nb_philosophers)
        	printf("\nphilo id = %d, total meal = %d, last meal = %d", philo[i].id, philo[i].total_meals, philo[i].last_meal);
*/
if (data.nb_philosophers == 1)
        one_philo(&data);
    else
        do_activities_stimultanously(&data);

  //free_all(data);
    return (0);
}
