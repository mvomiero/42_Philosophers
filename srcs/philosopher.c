/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:07:20 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/20 14:36:57 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[1]]);
	write_status(philo, false, GOT_FORK_2);
	//write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	//printf("HEREEEEE %d meal time lock\n", philo->id);
	philo->last_meal = get_time_in_ms();
	write_status(philo, false, EATING);
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_action(philo->data, philo->data->time_to_eat);
	if (dinner_is_over(philo->data) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[0]]);
	philo_action(philo->data, philo->data->time_to_sleep);
}

/* think_routiine:
	Thinking is the only action whose duration is not specified. In order to get
	the philosopher to "pause" for a determined amount of time,
	letting the forks free to the other	to eat, but at the same time 
	to start to eat before the dieing. The formula is here under inside the 
	function. 
	The function accepts a bool as parameter deciding if the action will be 
	printed or not, since the function is called two times:
	at the beginning to let odd-id philos to start first, and then in the normal
	philo routine.
 */
static void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->data->time_to_die 
				- philo->data->time_to_eat 	- philo->data->time_to_sleep) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (silent == false)
		write_status(philo, false, THINKING);
	philo_action(philo->data, time_to_think);
}

static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	philo_action(philo->data, philo->data->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[0]]);
	return (NULL);
}


/* philosopher_routine:
	the routine function for the philosphers threads. in the pthread_create 
	function the t_philo struct is passed as argument, so first step is to cast
	the void pointer to the actual datatype.
	Follows a check for particular conditions, where the philosopher hasn't to 
	eat or hasn't time to live, the function will just be returned.
	After that, the last time is initialized to the genereal start time. It's 
	here needed a mutex to protect the philo->last meal variable, that will be
	accessed by the waiter to check the situation as well.
	If the philosopher is just one, a particular routine is developed.
	if the philospher has a odd id number, will start the routine by thinking, 
	to allow the even id philophers to start first.
	Then, the standard routine is started, until the dinner is not over.
	At the end of the function, NULL is returned (= no problems).
 */
void	*philosopher_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->must_eat_count == 0 || philo->data->time_to_die == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (philo->data->nb_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, true);
	while (dinner_is_over(philo->data) == false)
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
	}
	return (NULL);
}