/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:21:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 12:58:53 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* get_time_in_ms:
	gets the time in seconds and microseconds since the Epoch (1970-01-01 
	00:00:00 +0000 (UTC)). It's stored in the timeval struct. The operations
	are to get the value in milliseconds (required from the assignement).
	1 sec == 1000 milliseconds.
	1 sec == 1000000 microseconds (== 1000 milliseconds).
	functions: --> sleep takes seconds as input;
			   --> usleep thakes microseconds as input.
 */
time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* philo_action:
	a philosopher performs an action for a given amount of time.
 */
void	philo_action(t_data *data, time_t action_time)
{
	time_t	stop_action;

	stop_action = get_time_in_ms() + action_time;
	while (get_time_in_ms() < stop_action)
	{
		if (dinner_is_over(data))
			break ;
		usleep(100);
	}
}
