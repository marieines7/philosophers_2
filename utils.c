/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:39:24 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/21 16:39:26 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int    current_timestamp(void)
{
    long int time;
    struct timeval current_time;

    time = 0;
    gettimeofday(&current_time, NULL);
    time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
    return (time);
}

void    timer(int activity_duration)
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
    pthread_mutex_lock(&philo->data->end_simulation);
    if (philo->data->stop == 1)
    return ;
    pthread_mutex_unlock(&philo->data->end_simulation);
    pthread_mutex_lock(&philo->data->print_activity); 
    printf("%ldms:  philosopher %d   %s\n", current_timestamp() - philo->data->start_time, philo->id, activity);
    pthread_mutex_unlock(&philo->data->print_activity);
}
