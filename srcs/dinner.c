/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:03:15 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/29 13:22:40 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
 
bool	start_dinner(t_data *data)
{
	int	i;

	data->start_time = get_time_in_ms();
	// + (data->nb_philos * 2 * 10);
	i = 0;
	//printf(" START TIME is: %ld", data->start_time);
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philosopher_routine, data->philos[i]) != 0)
			return (printf("philo: thread error!\n"), free_data(data), NULL);
		//printf("phlio thread initialized\n");
		//printf(" PHILO START TIME is: %ld", get_time_in_ms());
		i++;
	}
	if (data->nb_philos > 1)
	{
		if (pthread_create(&data->waiter, NULL,
				&waiter_routine, data) != 0)
			return (printf("philo: thread error!\n"), free_data(data), NULL);
	}
	
	return (true);
}

void	stop_dinner(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->nb_philos > 1)
		pthread_join(data->waiter, NULL);
	destroy_mutexes(data);
	free_data(data);
}

bool dinner_is_over(t_data *data)
{
	bool r;

	r = false;
	pthread_mutex_lock(&data->dinner_stop_lock);
	if (data->dinner_stop == true)
		r = true;
	pthread_mutex_unlock(&data->dinner_stop_lock);
	return (r);
}