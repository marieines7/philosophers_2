/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:08 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/22 15:47:22 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].id = i;
		data->philo[i].last_meal = current_timestamp();
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		if (i == data->nb_philosophers - 1)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
	}
}

void	start_lives_simultaneously(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philosophers)
		if ((i % 2) == 0)
			pthread_create(&data->philo[i].philo_life, \
				NULL, &simulation, &data->philo[i]);
	i = -1;
	while (++i < data->nb_philosophers)
	{
		if ((i % 2) == 1)
		{
			usleep(100);
			pthread_create(&data->philo[i].philo_life, \
				NULL, &simulation, &data->philo[i]);
		}
	}
	pthread_create(&data->end_simulation, NULL, &end_simulation, data);
	i = -1;
	while (++i < data->nb_philosophers)
		pthread_join(data->philo[i].philo_life, NULL);
	pthread_join(data->end_simulation, NULL);
}

void	one_philo(t_philo *philo)
{
	print_activity(philo, "has taken a fork\n");
	timer(philo->data->time_to_die);
	print_activity(philo, "is dead\n");
}

int	init(t_data *data)
{
	data->philo = malloc(data->nb_philosophers * sizeof(t_philo));
	if (!data->philo)
		return (0);
	data->forks = malloc(data->nb_philosophers * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	pthread_mutex_init(&data->print_activity, NULL);
	data->start_time = current_timestamp();
	init_philo(data);
	if (data->nb_philosophers == 1)
	{
		one_philo(data->philo);
		free_all(data);
		return (1);
	}
	start_lives_simultaneously(data);
	free_all(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!right_args(ac, av))
		return (0);
	save_right_data(&data, ac, av);
	init(&data);
	return (0);
}
