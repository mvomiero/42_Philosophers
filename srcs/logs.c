/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:32:12 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/11 15:57:43 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time,
		philo->id + 1, str);
}

void	write_status(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->data->write_lock);
	// REMEMBER TO COMMENT OUT THIS BLOCK OF CODE
	(void)reaper_report;
	if (dinner_is_over(philo->data) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
/* 	if (DEBUG_FORMATTING == true)
	{
		write_status_debug(philo, status);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	} */
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->write_lock);
}