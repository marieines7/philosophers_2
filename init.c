/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <mloubet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:08 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/21 17:27:41 by mloubet          ###   ########.fr       */
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

int check_death(t_data *data)
{
	unsigned int i;

	i = 0;
	while(i < data->nb_philosophers)
	{
		  if ((current_timestamp() - data->philo->last_meal) > data->time_to_die)
  		  {
			pthread_mutex_lock(&data->end_simulation);
			data->stop = 1;
			pthread_mutex_unlock(&data->end_simulation);
        		pthread_mutex_lock(&data->print_activity);
        		printf("%ldms philosopher %d is dead\n", current_timestamp() - data->start_time, data->philo->id);
       		 	pthread_mutex_unlock(&data->print_activity);
       			 return(1);
   		 }
			i++;
	}
	return(0);
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
	return(0);
}

int	do_activities_stimultanously(t_data *data)
{
	unsigned int	i;
//	int		end_simulation;
	i = 0;
	while (i < data->nb_philosophers)
	{
		if ((i % 2) == 0)
		{
			if (pthread_create(&data->philo[i].philo_life, NULL, &simulation, &data->philo[i]) != 0)
			{
				printf("error creating philo life\n");
				return(0);
			}
				
		}
		i++;
	}
	i = 0;
	while (i < data->nb_philosophers)
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
		i++;
	}
	int end_simulation = 0;
	while(1)
	{
		end_simulation = check_death(data);
		if (end_simulation == 1)
			break;
	}
	
	i = 0;
	while (i < data->nb_philosophers)
	{
		if(pthread_join(data->philo[i].philo_life, NULL) != 0)
		{
			printf("error join\n");
			return (0);
		}
		i++;
	}
	printf("fin game\n");	
	return(0);
}

