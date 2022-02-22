/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mloubet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:59:40 by mloubet           #+#    #+#             */
/*   Updated: 2022/02/22 15:55:06 by mloubet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	philo_life;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int			id;
	int			status;
	int			total_meals;
	unsigned long		last_meal;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	pthread_t	end_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_activity;
	pthread_mutex_t	eating;
	t_philo			*philo;
	int			nb_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			total_meals_for_each_philo;
	unsigned long		start_time;
	int			stop;
	int			total_meals_count;
}		t_data;

int				right_args(int ac, char **av);
int				save_right_data(t_data *data, int ac, char **av);
int				init(t_data *data);
void			*simulation(void *arg);
void			*end_simulation(void *arg);
void			print_activity(t_philo *philo, char *activity);
unsigned long	current_timestamp(void);
unsigned long	when_in_ms(unsigned long start);
int				ft_atoi(char *str);
void			timer(int activity_duration);
void			free_all(t_data *data);
int				ft_strcmp(char *s, char *t);

#endif
