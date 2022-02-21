/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:08 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/21 22:13:42 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philosophers)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].total_meals = 0;
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		data->philo[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->nb_philosophers)
	{
		if (i == data->nb_philosophers - 1)
			data->philo[i].right_fork = &data->philo[0].left_fork;
		else
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}

int	philo_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_activity(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_activity(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->eating);
	philo->last_meal = current_timestamp();
	philo->total_meals++;
	printf("total mels in philo life %d\n", philo->total_meals);
	pthread_mutex_unlock(&philo->data->eating);
	print_activity(philo, "is eating");
	timer(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_activity(philo, "is sleeping");
	timer(philo->data->time_to_sleep);
	print_activity(philo, "is thinking");
	return (0);
}

int	do_activities_stimultanously(t_data *data)
{
	unsigned int	i;
	int		end_simulation;

	i = 0;
	while (i < data->nb_philosophers)
	{
		if ((i % 2) == 0)
			pthread_create(&data->philo[i].philo_life, \
				NULL, &simulation, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philosophers)
	{
		if ((i % 2) == 1)
		{
			usleep(100);
			pthread_create(&data->philo[i].philo_life, \
				NULL, &simulation, &data->philo[i]);
		}
		i++;
	}
	end_simulation = 0;
	while (1)
	{
		end_simulation = check_death(data->philo);
		if (end_simulation == 1)
			return (0);
	}
	i = 0;
	while (i < data->nb_philosophers)
	{
		pthread_join(data->philo[i].philo_life, NULL);
		i++;
	}
	printf("fin game\n");	
	return (0);
}
