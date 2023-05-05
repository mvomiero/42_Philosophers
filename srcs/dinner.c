/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:03:15 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 12:55:07 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* start_dinner:
	initializes the dinner, getting first the start time and storing in the data
	struct, then creating the threads for the corresponding philosophers.
	If there is more then one philosopher, the waiter thread is created as well.
 */
bool	start_dinner(t_data *data)
{
	int	i;

	data->start_time = get_time_in_ms();
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philosopher_routine, data->philos[i]) != 0)
			return (printf("philo: thread error!\n"), free_data(data), NULL);
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

/* stop_dinner:
	stops the dinner: all threads are joined, mutexes are destroyed, data is 
	freed.
	Joining a thread means to wait for the specified thread to teminate. 
	It's similar to a wait call for children processes in the main process.
	In this way, we are sure that all threads are terminated and we can safely
	stop the dinner and free the data.
 */
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
