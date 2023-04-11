/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:03:05 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/10 13:21:23 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!forks)
		return (printf("philo: malloc error!\n"), free_data(data), NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (printf("philo: mutex error!\n"), free_data(data), NULL);
			// here you have to destroy the already allocated mutexes
		i++;
	}
	return (forks);
}

static void	assign_forks(t_philo *philo)
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

static t_philo	**init_philosophers(t_data *data)
{
	t_philo	**philos;
	int		i;

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
			// here you have to destroy the already allocated mutexes
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

static bool	init_global_mutexes(t_data *data)
{
	data->fork_locks = init_forks(data);
	if (!data->fork_locks)
		return (false);
	if (pthread_mutex_init(&data->sim_stop_lock, 0) != 0)
		return (printf("philo: mutex error!\n"), free_data(data), NULL);
		// here you have to destroy the already allocated mutexes
	if (pthread_mutex_init(&data->write_lock, 0) != 0)
		return (printf("philo: mutex error!\n"), free_data(data), NULL);
		// here you have to destroy the already allocated mutexes
	return (true);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

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
	if (!init_global_mutexes(data))
		return (NULL);
	data->sim_stop = false;
	return (data);
}