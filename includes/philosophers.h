/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:35:50 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 12:58:36 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

/* STRUCTS */

typedef struct s_philo	t_philo;

typedef struct s_data
{
	time_t			start_time;
	int				nb_philos;
	pthread_t		waiter;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	bool			dinner_stop;
	pthread_mutex_t	dinner_stop_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				times_ate;
	int				fork[2];
	pthread_mutex_t	meal_time_lock;
	time_t			last_meal;
	t_data			*data;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

/* PARSING */

int		int_atoi(char *str);

/* INITIALIZATION */

t_data	*init_data(int ac, char **av);

/* EXIT_ERROR */

void	free_data(t_data *data);
void	destroy_mutexes(t_data *data);

/* DINNER */

bool	start_dinner(t_data *data);
void	stop_dinner(t_data	*data);

/* PHILOSOPHER */

void	*philosopher_routine(void *args);

/* UTILS_TIME */

time_t	get_time_in_ms(void);
void	philo_action(t_data *data, time_t sleep_time);

/* LOGS */

void	write_status(t_philo *philo, t_status status);

/* WAITER */

bool	dinner_is_over(t_data *data);
void	*waiter_routine(void *args);

#endif
