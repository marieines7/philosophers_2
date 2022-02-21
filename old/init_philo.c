#include "philo.h"

/*
void	add_philo(t_philo *philo, unsigned int i)
{
	printf("je passe dans add philo\n");
	philo[i].id = i + 1;
	philo[i].total_meals = 0;
	philo[i].last_meal = 0;
	pthread_mutex_init(&philo[i].left_fork, NULL);
	philo[i].right_fork = NULL;
}

void	share_left_fork_with_right_neighbour(t_philo *philo, t_data *data)
{
	unsigned int	i;
	//t_data	*data;

	//data = philo->data;
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

void	init_philos(t_philo *philo, t_data *data)
{
	unsigned int     i;
	i = 0;
printf("je passe dans init philo");
//	t_data *data;

//	data = philo->data;
	philo = malloc(sizeof(t_philo) * data->nb_philosophers);
	printf("nb de philos = %d\n", data->nb_philosophers);
	while (i < data->nb_philosophers)
	{
		add_philo(philo, i);
		i++;
	}
	share_left_fork_with_right_neighbour(philo, data);
}
*/
