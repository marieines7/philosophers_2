#include "philo.h"

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
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(&data->end_simulation);
    if (data->one_philo_died == 1)
       return ;
    pthread_mutex_unlock(&data->end_simulation);
    pthread_mutex_lock(&data->print_activity); 
    printf("%ldms:  philosopher %d   %s\n", current_timestamp() - data->start_time, philo->id, activity); // checker pour le +1 philo id
    pthread_mutex_unlock(&data->print_activity);
}

void free_all(t_data *data)
{
	int i;
    t_philo *philo;

	i = -1;
    philo = data->philo;
	while (++i < data->nb_philosophers)
		pthread_mutex_destroy(&philo[i].left_fork);
	pthread_mutex_destroy(&data->print_activity);
	pthread_mutex_destroy(&data->eating);
    pthread_mutex_destroy(&data->eating);
    pthread_mutex_destroy(&data->end_simulation);
 //   free(&philo);
}