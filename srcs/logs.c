/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:32:12 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 12:27:18 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* print_status:
	gets the time and prints the status of the philosopher (philo_id + 1 since
	it starts from philo 1 and not philo 0)
 */
static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time,
		philo->id + 1, str);
}

/* write_status:
	loks the log mutex and prints the corresponding status. If the dinner is 
	over just returns.
 */
void	write_status(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	if (dinner_is_over(philo->data) == true)
	{
		pthread_mutex_unlock(&philo->data->log_mutex);
		return ;
	}
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
	pthread_mutex_unlock(&philo->data->log_mutex);
}