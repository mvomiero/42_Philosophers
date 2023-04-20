/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:21:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/16 13:21:23 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time_in_ms(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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