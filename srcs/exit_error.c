/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:04:03 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/05 12:22:30 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	unsigned int	i;

	if (!data)
		return ;
	if (data->fork_locks != NULL)
		free(data->fork_locks);
	if (data->philos != NULL)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (data->philos[i] != NULL)
				free(data->philos[i]);
			i++;
		}
		free(data->philos);
	}
	free(data);
}

