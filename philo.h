
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



typedef struct  s_philo
{
	int id;
	pthread_t philo_life;
	pthread_mutex_t	left_fork;
    	pthread_mutex_t *right_fork;
	int state;
	unsigned long last_meal;
	unsigned int total_meals;
	struct  s_data *data;
}   t_philo;

typedef struct  s_data
{
	t_philo *philo;
	pthread_mutex_t eating; //forks
	pthread_mutex_t end_simulation;//monitor. pthread_t ou pthread_mutex??
	pthread_mutex_t print_activity;
	pthread_mutex_t *forks;
	unsigned long start_time;
	unsigned int nb_philosophers;
	unsigned long time_to_die;
	int time_to_eat;
	int time_to_sleep;
	unsigned int total_meals_for_each_philo;
	int	stop;
	int option;
	int total_meals; //meal count
}   t_data;

//utils
long int current_timestamp(void);
void timer(int activity_duration);

void    print_activity(t_philo *philo, char *activity);

//parsing
int ft_atoi(char *s);
int all_are_digits(char **s);
int	right_args(int ac, char **av);
int    save_data(int ac, char **av, t_data *data);

//init
int	init_philos(t_data *data);
int philo_life(t_philo *philo);
int	do_activities_stimultanously(t_data *data);
void one_philo(t_philo *philo);
void free_all(t_data * data);
int init_simulation(t_data *data);

int one_philo_died(t_philo *philo);
void *simulation(void *arg);
int check_end_simulation(t_philo *philo);
int end_simulation(t_philo *philo);
int end_simulation_2(t_philo *philo);

int continue_simulation(t_philo *philo);


#endif