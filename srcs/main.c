/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:31:18 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 13:55:58 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (printf("ARGS: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"),
			EXIT_FAILURE);
	if (!input_check(ac, av))
		return (printf("Wrong arguments!\n"), EXIT_FAILURE);
	data = init_data(ac, av);
	if (!data)
		return (EXIT_FAILURE);
	if (!start_dinner(data))
		return (EXIT_FAILURE);
	stop_dinner(data);
	return (EXIT_SUCCESS);
}
