/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:31:18 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/07 13:09:48 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	*data;

	//data = NULL;
	data = init_data(ac, av);
	if (!data)
		return (EXIT_FAILURE);	

	printf("%d\n", int_atoi("88"));
	printf("%d\n", data->nb_philos);
	printf("%ld\n", data->time_to_die);
	printf("%ld\n", data->time_to_eat);
	printf("%ld\n", data->time_to_sleep);
	
	struct timeval		tv;
	gettimeofday(&tv, NULL);
	printf("%ld\n", tv.tv_sec);
	if (!start_simulation(data))
		return(EXIT_FAILURE);
	//if (data->philos)
	//	return (printf("philo: ciao ciao!\n"), free_data(data), 0);

	// TO DO: STOP SIMULATION!!

	(void)data;

	
}