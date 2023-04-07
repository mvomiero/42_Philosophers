/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:03:15 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/07 15:35:17 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
 
bool	start_simulation(t_data *data)
{
	unsigned int	i;

	data->start_time = get_time_in_ms();
	// + (data->nb_philos * 2 * 10);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&philosopher, data->philos[i]) != 0)
			return (printf("philo: thread error!\n"), free_data(data), NULL);
		i++;
	}
	if (data->nb_philos > 1)
	{
		if (pthread_create(&data->grim_reaper, NULL,
				&grim_reaper, data) != 0)
			return (printf("philo: thread error!\n"), free_data(data), NULL);
	}
	return (true);
}

void	stop_simulation(t_data	*data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->nb_philos > 1)
		pthread_join(data->grim_reaper, NULL);
	destroy_mutexes(data);
	free_data(data);
}