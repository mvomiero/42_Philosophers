/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:45:37 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 13:01:39 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* dinner_stop_flag:
	uses the corresponding mutex to set the dinner_stop bool according to the 
	state bool passed as parameter.
 */
static void	dinner_stop_flag(t_data *data, bool state)
{
	pthread_mutex_lock(&data->dinner_stop_mutex);
	data->dinner_stop = state;
	pthread_mutex_unlock(&data->dinner_stop_mutex);
}

/* check_kill_philo:
	bool that checks if a philosopher should die. 
	Id does it simply checking the current time and the time of the last meal
	If so, the function writes the 
	corresponding status, sets the dinner_stop flag to true and returns true:
	the waiter will then know (thanks to the stop_condition_reached function) 
	that the dinner has to stop.
 */
static bool	check_kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->data->time_to_die)
	{
		dinner_stop_flag(philo->data, true);
		write_status(philo, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/* stop_condition_reached:
	checks the two stopping conditions, returning true in case one of these 
	conditions is met:
	1 - a philosopher should die
	2 - everybody ate enough. To check if everybody ate enough, a bool is 
		defined and set true to
		check if every philosopher ate enough, it will be switched to false in
		case a pilosopher didn't eat enough. The -1 condition is just to protect
		the initialization value, which is -1 and of course will always be less 
		then must_eat_count. 
	return value is true if one of the stopping conditions is met, false if the
	funcions runs until the end. 
 */
static bool	stop_condition_reached(t_data *data)
{
	int		i;
	bool	all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i]->meal_time_lock);
		if (check_kill_philo(data->philos[i]))
			return (true);
		if (data->must_eat_count != -1)
			if (data->philos[i]->times_ate < data->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		i++;
	}
	if (data->must_eat_count != -1 && all_ate_enough == true)
	{
		dinner_stop_flag(data, true);
		return (true);
	}
	return (false);
}

/* waiter:
	the routine function for the "waiter" thread returns a void pointer and
	accepts a void pointer as argument. By convention, the return value in case
	of no problems is NULL. the void pointer given as argument corresponds to 
	the argument of the pthread_create function (see dinner_start where this 
	function is executed), therefore it has to be first casted from void pointer
	to the actual datatype. 
	After setting the dinner_stop_flag to false, an infinite loop is started: 
	every 1000 microseconds (microseconds = 10 to -6, 0.000001 seconds) checks 
	if the stop condition is reached and if so, just returns null and 
	starts the closing procedures:
	the start_dinner function is returned and in the main the stop_dinner 
	function is started (where all the processes are joined).
 */
void	*waiter_routine(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	if (data->must_eat_count == 0)
		return (NULL);
	dinner_stop_flag(data, false);
	while (1)
	{
		if (stop_condition_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
}
