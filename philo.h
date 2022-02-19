
#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

/*
#define RED "\033[91m"
#define PINK"\033[95m"
#define YELLOW "\033[93m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define  END "\0330m"
*/

typedef struct  s_philo
{
   // struct  s_philo *next;
    int id;
    int total_meals;
    int last_meal;
    /*int right_fork_int;
    int left_fork_int;*/
    pthread_t philo;
    pthread_mutex_t left_fork;
    pthread_mutex_t *right_fork;
    struct  s_data *data;

}   t_philo;

typedef struct  s_data
{
    struct  s_data *next;
    unsigned int nb_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int total_meals_for_each_philo;
    int one_philo_died;
    long start_time; // mettre timestruct?
    pthread_mutex_t print_activity;
    pthread_mutex_t end_simulation;
    pthread_mutex_t eating;
    t_philo *philo;
 
}   t_data;

/*parsing*/
int   save_data(int ac, char **av, t_data *data);
int	get_right_args(int ac, char **av);

/*init philo*/
void	add_philo(t_philo *philo, unsigned int i);
void	share_left_fork_with_right_neighbour(t_data *data);
void	init_philos(t_data *data);

int ft_atoi(char *s);
 
int all_are_digits(char **s);
void	ft_free_lst(t_philo **list);

void	printstack(t_data *s);
t_philo *ft_lstnew(int philo_id);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);



void	*ft_calloc(size_t count, size_t size);
void    print_activity(t_philo *philo, char *action);
long int current_timestamp(void);
void timer(int activity_duration);
void one_philo(t_data *data);

void free_all(t_data *data);

#endif

