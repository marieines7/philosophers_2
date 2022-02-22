/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:39:24 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/21 21:53:00 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_timestamp(void)
{
	long int	time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	timer(int activity_duration)
{
	long int	start_time;
	long int	current_time;

	start_time = current_timestamp();
	current_time = start_time;
	while ((current_time - start_time) < activity_duration)
	{
		usleep(100);
		current_time = current_timestamp();
	}
}

unsigned long	when_in_ms(unsigned long start_time)
{
	return(current_timestamp() - start_time);
}

void free_all(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_philosophers)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->philo);
	free(data->forks);

}

int	ft_strcmp(char *s, char *t)
{
	while (*s && (*s == *t))
	{
		s++;
		t++;
	}
	return (*s - *t);
}