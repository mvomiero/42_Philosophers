/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:08:28 by mvomiero          #+#    #+#             */
/*   Updated: 2023/05/05 13:22:03 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* int_atoi:
	variation of the standard atoi. Result can only be positive. An unsigned int
	is used as temp variable in order to check for results greather then INT_MAX
 */
int	int_atoi(char *str)
{
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
		if (nb > INT_MAX)
			return (-1);
	}
	return ((int)nb);
}

/* dinner is over:
	bool used to check if the dinner is over (checking the data->dinner_stop 
	bool). just returns true if the dinner is over.
 */
bool	dinner_is_over(t_data *data)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&data->dinner_stop_mutex);
	if (data->dinner_stop == true)
		r = true;
	pthread_mutex_unlock(&data->dinner_stop_mutex);
	return (r);
}

bool	input_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!int_atoi(av[i]))
			return (false);
		i++;
	}
	return (true);
}
