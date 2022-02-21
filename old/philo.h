
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

//repartir avec que la structure philo qui pourrait s appeler tab_philo
//et qui contiendrait les philo (threads)
//philo->philo[i]
typedef struct  s_philo
{
   // struct  s_philo *next;
    int id;
    long unsigned int last_meal;
    unsigned int nb_philosophers;
    long unsigned int time_to_die;
    long unsigned int time_to_eat;
    long unsigned int time_to_sleep;
       int total_meals_for_each_philo;
    int total_meals;
    int option;
    /*int right_fork_int;
    int left_fork_int;*/
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t is_eating;
   
    struct  s_data *data;

}   t_philo;

typedef struct  s_data
{
    /*
   // struct  s_data *next;
    unsigned int nb_philosophers;
    int option;
     long unsigned int time_to_die;
     long unsigned int time_to_eat;
     long unsigned int time_to_sleep;
    int total_meals_for_each_philo;
    */
    int one_philo_died;
    long start_time; // mettre timestruct?
    pthread_mutex_t print_activity;
   // pthread_mutex_t end_simulation;
   // pthread_mutex_t eating;
   
    pthread_mutex_t forks[200];
    pthread_t philo_lives[200];
    
 
}   t_data;


int	right_args(int ac, char **av);

void	add_philo(t_philo *philo, unsigned int i);
void share_left_fork_with_right_neighbour(t_philo *philo);

int ft_atoi(char *s);
 
int all_are_digits(char **s);
void	ft_free_lst(t_philo **list);

void	printstack(t_data *s);
t_philo *ft_lstnew(int philo_id);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);


//void init_philos(t_data *data);
void	init_philos(t_philo *philo, char **av, int option);
void	*ft_calloc(size_t count, size_t size);
void    print_activity(t_philo *philo, char *action);
long int current_timestamp(void);
void timer(int activity_duration);
void one_philo(t_data *data);

void free_all(t_data *data);

#endif

