/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:03:05 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 12:07:08 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* init_forks:
	an array is mallocated to store the mutexes of the corresponding forks
 */
static pthread_mutex_t *init_forks(t_data *data)
{
	pthread_mutex_t *forks;
	int i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!forks)
		return (printf("philo: malloc error!\n"), free_data(data), NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (printf("philo: mutex error!\n"), free_data(data), NULL);
		i++;
	}
	return (forks);
}

/* assign_forks:
	if every philosopher would take first his fork on the left we would have a 
	deadlock: everybody has a fork but nobody can start to eat.
	To solve this problem: even philosophers aim first to their right fork and 
	after the left one, odd philophers the contrary.
	(philo->id + 1) % philo->data->nb_philos ---> this formula is to assign to 
	the last philosopher the first fork in order to "complete" the circle of the
	round table.
 */
static void assign_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->nb_philos;
		philo->fork[1] = philo->id;
	}
	else
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % philo->data->nb_philos;
	}
}

/* init_philosophers:
	an array of structs is mallocated.
	for each philosopher, the struct is created and mallocated, the mutex for 
	the meal time is created and the forks are assigned.
 */
static t_philo **init_philosophers(t_data *data)
{
	t_philo **philos;
	int i;

	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
		return (printf("philo: malloc error!\n"), free_data(data), NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (printf("philo: malloc error!\n"), free_data(data), NULL);
		if (pthread_mutex_init(&philos[i]->meal_time_lock, NULL) != 0)
			return (printf("philo: mutex error!\n"), free_data(data), NULL);
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

/* init_mutexes:
	- the mutexs for the corresponding forks are created
	- dinner stop mutex created
	- log mutex created
 */
static bool init_mutexes(t_data *data)
{
	data->fork_locks = init_forks(data);
	if (!data->fork_locks)
		return (false);
	if (pthread_mutex_init(&data->dinner_stop_mutex, 0) != 0)
		return (printf("philo: mutex error!\n"), free_data(data), NULL);
	if (pthread_mutex_init(&data->log_mutex, 0) != 0)
		return (printf("philo: mutex error!\n"), free_data(data), NULL);
	return (true);
}

/* init_data:
	initializes all the elements needed for the execution and parses the
	arguments:
	- malloc of the struct;
	- parsing of the parameters into integers
	- initializes the philosophers array of structs (assigning forks as well)
	- initializes the mutexes (forks + dinner_stop + write)

 */
t_data *init_data(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (printf("philo: malloc error!\n"), NULL);
	data->nb_philos = int_atoi(av[1]);
	data->time_to_die = int_atoi(av[2]);
	data->time_to_eat = int_atoi(av[3]);
	data->time_to_sleep = int_atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = int_atoi(av[5]);
	data->philos = init_philosophers(data);
	if (!data->philos)
		return (NULL);
	if (!init_mutexes(data))
		return (NULL);
	data->dinner_stop = false;
	return (data);
}