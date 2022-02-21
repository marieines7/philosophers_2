#include "philo.h"

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
/*
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
            philo->data->stop = 1;
            break;
        }
        i++;
    }
    pthread_mutex_lock(&philo->data->end_simulation);
    if ((philo->data->stop == 1) ||
	((philo->data->option == 1) && ((int)philo->data->total_meals_for_each_philo != -1) && (all_had_enough_to_eat == 1)))
        return(1);
    pthread_mutex_unlock(&philo->data->end_simulation);
    return (0);
}
*/
/*
void *simulation(void *arg)
{
	t_philo *philo;
//	int	life;
  // int     death;

    philo = (t_philo *)arg;
	//mutex_lock
	life = philo->data->stop;
//	mutex_unlock
	printf("philo %d has eaten %d meals", philo->id, philo->total_meals);
	//while ((philo->data->option == 1 && (philo->total_meals < philo->data->total_meals_for_each_philo)))
	while(is_alive == 0)
	{
		philo_life(philo);
		//mutex_lock
		life = philo->data->stop;
		//mutex_unlock
	printf("je passe dans simulation. philo %d total meals eaten = %d; total meals to eat = %d\n", philo->id, philo->total_meals, philo->data->total_meals_for_each_philo);
	}
	//printf("philo %d: ok je suis en train de vivre\n", philo->id);
	printf("here for philo number %d\n", philo->id);
	return(0);
}
*/
void *simulation(void *arg)
{
	t_philo *philo;
	//int end_simulation;
    	
	philo = (t_philo *)arg;
	/*pthread_mutex_lock(&philo->data->end_simulation);
	end_simulation = philo->data->stop;
	pthread_mutex_unlock(&philo->data->end_simulation);
	while(end_simulation == 0)
	{
		philo_life(philo);
		pthread_mutex_lock(&philo->data->end_simulation);
		end_simulation = philo->data->stop;
		pthread_mutex_unlock(&philo->data->end_simulation);
	}
	*/
	while(1)
	{
		philo_life(philo);
	}
	return (0);
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


int end_simulation(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->eating);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->end_simulation);
	return(1);
}

int end_simulation_2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_activity);
    printf("%ldms philo %d is dead\n", current_timestamp(), philo->id);
    pthread_mutex_unlock(&philo->data->print_activity);
	pthread_mutex_lock(&philo->data->end_simulation);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->end_simulation);
	pthread_mutex_unlock(&philo->data->eating);
	return(1);
}

int continue_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_simulation);
	philo->data->stop = 0;
	pthread_mutex_unlock(&philo->data->end_simulation);
	return(0);
}

int check_end_simulation(t_philo *philo)
{
	unsigned int i;
	unsigned int j;

	i = -1;
	j = 0;
	while(++i < philo->data->nb_philosophers)
	{
		pthread_mutex_lock(&philo[i].data->eating);
		if(philo[i].total_meals == philo[i].data->total_meals_for_each_philo)
		{
			j++;
			pthread_mutex_lock(&philo->data->end_simulation);
			if(j == philo->data->nb_philosophers)
				return(end_simulation(philo));
		}
		if ((current_timestamp() - philo[i].last_meal) > philo[i].data->time_to_die) //death
				return(end_simulation_2(&philo[i]));
		else
			continue_simulation(&philo[i]);
		pthread_mutex_lock(&philo[i].data->eating);
	}
	return(0);
}


/*
int	check_life(t_philo *philo)
{

	//check everyone eat 
	// if everyone eat == nb_meals -> philo->data->life = 1; && return (1) mutex
	// if philo doe  -> philo->data->life = 1; && return (1) mutex
	// else philo->data->life = 0 mutex return (0)
}
*/

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
