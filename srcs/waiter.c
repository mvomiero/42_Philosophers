/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:45:37 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/07 13:05:45 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	has_simulation_stopped(t_data *data)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&data->sim_stop_lock);
	if (data->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&data->sim_stop_lock);
	return (r);
}

/* set_sim_stop_flag:
*	Sets the simulation stop flag to true or false. Only the grim
*	reaper thread can set this flag. If the simulation stop flag is
*	set to true, that means the simulation has met an end condition.
*/
static void	set_sim_stop_flag(t_data *data, bool state)
{
	pthread_mutex_lock(&data->sim_stop_lock);
		data->sim_stop = state;
	pthread_mutex_unlock(&data->sim_stop_lock);
}

/* kill_philo:
*	Checks if the philosopher must be killed by comparing the
*	time since the philosopher's last meal and the time_to_die parameter.
*	If it is time for the philosopher to die, sets the simulation stop
*	flag and displays the death status.
*	Returns true if the philosopher has been killed, false if not.
*/
static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->data->time_to_die)
	{
		set_sim_stop_flag(philo->data, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/* end_condition_reached:
*	Checks each philosopher to see if one of two end conditions
*	has been reached. Stops the simulation if a philosopher needs
*	to be killed, or if every philosopher has eaten enough.
*	Returns true if an end condition has been reached, false if not.
*/
static bool	end_condition_reached(t_data *data)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i]->meal_time_lock);
		if (kill_philo(data->philos[i]))
			return (true);
		if (data->must_eat_count != -1)
			if (data->philos[i]->times_ate
				< (unsigned int)data->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&data->philos[i]->meal_time_lock);
		i++;
	}
	if (data->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(data, true);
		return (true);
	}
	return (false);
}

/* grim_reaper:
*	The grim reaper thread's routine. Checks if a philosopher must
*	be killed and if all philosophers ate enough. If one of those two
*	end conditions are reached, it stops the simulation.
*/
void	*grim_reaper(void *args)
{
	t_data			*data;

	data = (t_data *)args;
	if (data->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(data, false);
	//sim_start_delay(data->start_time);
	printf("GRIM REAPER start time is: %ld\n", data->start_time);

	while (true)
	{
		if (end_condition_reached(data) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
