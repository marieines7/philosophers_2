#include "philo.h"


void	add_philo(t_philo *philo, unsigned int i)
//void	add_philo(t_data *data, pthread_mutex_t **forks, unsigned int i)
{
	philo[i].id = i + 1;
	philo[i].total_meals = 0;
	philo[i].last_meal = 0;
	/*philo[i].left_fork = */
	pthread_mutex_init(&philo[i].left_fork, NULL);
	philo[i].right_fork = NULL;
}

void	share_left_fork_with_right_neighbour(t_data *data)
{
	unsigned int	i;
	t_philo	*philo;

	philo = data->philo;
	i = -1;
	if (data->nb_philosophers > 1)
	{
		while (++i < data->nb_philosophers)
		{
				printf("ok\n");
				philo[i].right_fork = &philo[(i + 1) % data->nb_philosophers].left_fork;
		}	
	}
}

void	init_philos(t_data *data)
{
	unsigned int     i;
	//pthread_mutex_t *forks;

	i = 0;
	//philo = ft_calloc(data->nb_philosophers, sizeof(t_philo));
	data->philo = malloc(data->nb_philosophers * sizeof(t_philo));
	if (!data->philo)
        	return ;
//	data->philo = philo;
	while (++i <= data->nb_philosophers)
		add_philo(data->philo, i);
	share_left_fork_with_right_neighbour(data);
}