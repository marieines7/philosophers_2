/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:39:03 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/21 17:26:01 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_activity(t_philo *philo, char *activity)
{
	pthread_mutex_lock(&philo->data->print_activity);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->print_activity);
		return ;
	}
	printf("%ld %d %s\n", when_in_ms(philo->data->start_time), philo->id + 1, activity);
	if (ft_strcmp(activity, " is sleeping"))
		philo->data->total_meals_count++;
	pthread_mutex_unlock(&philo->data->print_activity);
}

void	philo_life(t_philo *philo)
{
	print_activity(philo, " is thinking");
	pthread_mutex_lock(philo->left_fork);
	print_activity(philo, " has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_activity(philo, " has taken a fork");
	print_activity(philo, " is eating");
	philo->last_meal = current_timestamp();
	timer(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_activity(philo, " is sleeping");
	timer(philo->data->time_to_sleep);
}

void	*simulation(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	i = 0;
	while (i != philo->data->total_meals_for_each_philo) // qd pazs doption 0 != -1 donc boucle infinie
	{
		if (philo->data->stop == 1)
			return (0);
		philo_life(philo);
		i++;
	}
	return (0);
}

void	*end_simulation(void *arg)
{
	int		i;
	t_data	*data;

	data = arg;
	while (data->total_meals_for_each_philo != 0) //valeur neg si pas de meal count donc entre dans la boucle
	{
		i = -1;
		while (++i < data->nb_philosophers)
		{
			if (data->total_meals_count == data->nb_philosophers * data->total_meals_for_each_philo) // pour loption ne sera jamais egal a -1;
				return (0);
			if (when_in_ms(data->philo[i].last_meal)
				> (unsigned long)data->time_to_die)
			{
				data->stop = 1;
				print_activity(&data->philo[i], "is dead");
				printf("%ld %d is dead\n", when_in_ms(data->start_time), data->philo->id + 1);
				return (NULL);		
			}
		}
	}
	return (NULL);
}
