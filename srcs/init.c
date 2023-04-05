/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:03:05 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/05 11:27:14 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
		//return (error_null(STR_ERR_MALLOC, NULL, 0));
	data->nb_philos = int_atoi(av[1]);
	data->time_to_die = int_atoi(av[2]);
	data->time_to_eat = int_atoi(av[3]);
	data->time_to_sleep = int_atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = int_atoi(av[5]);
	//data->philos = init_philosophers(data);
	//if (!data->philos)
	//	return (NULL);
	//if (!init_global_mutexes(data))
	//	return (NULL);
	data->sim_stop = false;
	return (data);
}