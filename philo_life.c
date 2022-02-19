#include "philo.h"

void one_philo(t_data *data)
{
    print_activity(data->philo, "has taken a fork\n");
    timer(data->time_to_die);
    print_activity(data->philo, "is dead\n");
}

/*
time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting their last meal or the beginning of the simulation,
it dies.
◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time they will need to keep the two forks.
◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.
◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.
*/

/*
void	free_all(t_data *data, pthread_mutex_t *forks)
{
	unsigned int	i;

	i = 0;
	while(++i <= data->nb_philos)
		pthread_mutex_destroy(&forks[i]);
	if (i == data->nb_philos)
		free(forks);
	//free faucheuse, printer, number of times ate, philos etc.
}



*/
/*



void destroy_mutexes(t_philo *philo, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philosophers)
		pthread_mutex_destroy(&philo[i].left_fork)
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->eatingtimes??);
}
*/
/*
void	print_activity(t_philo *philo, char *activity)
{
	long int time;
	int	dead;
	pthread_mutex_lock(&data->faucheuse)
	one_philo_is_dead = data->one_philo_died;
	pthread_mutex_lock(&data->faucheuse)
	if (one_philo_is_dead)
		return;
	if (get_time(philo->start_timexx))
		printf("%ldms philo %d %s\n", time, philo->id, activity);
}

*/

