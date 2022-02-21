#include "philo.h"

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
	{
		if (i == data->nb_philosophers - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork; //&left_fork a remettre?
		else
		data->philo[i].right_fork = &data->philo[i + 1].left_fork; //&left_fork a remettre?
		//data->philo[i].right_fork = &data->philo[(i + 1) % data->nb_philosophers].left_fork; //&left_fork a remettre?
		//printf("pour le philo %d, tu prend la fourchette droite du philo %d\n", i + 1 % data->nb_philosophers, i);
	}
	return (1);
}

void philo_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_activity(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_activity(philo, "has taken a fork");
 //is eating:
	pthread_mutex_lock(&philo->data->eating);
	philo->last_meal = current_timestamp(); //ou gettimeofday(&philo->last_eat, NULL); //philo->last_meal = current_timestamp(data->start_time);
	philo->total_meals++;
	printf("total mels in philo life %d\n", philo->total_meals);
	pthread_mutex_unlock(&philo->data->eating);
	print_activity(philo, "is eating");
	timer(philo->data->time_to_eat);

	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

    //is sleeping
	print_activity(philo, "is sleeping");
	timer(philo->data->time_to_sleep);
	//is thinking
    print_activity(philo, "is thinking");
	

}




int	do_activities_stimultanously(t_data *data)
{
	unsigned int	i;
//	int		end_simulation;
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
/*	while(1)
	{
		int end_simulation = check_end_simulation(data->philo);
		if (end_simulation == 1)
			return(1);
	}
*/	i = -1;
	while (++i < data->nb_philosophers)
	{
		if(pthread_join(data->philo[i].philo_life, NULL) != 0)
		{
			printf("error join\n");
			return (0);
		}
	}
	printf("fin game\n");	
	return(0);
}

