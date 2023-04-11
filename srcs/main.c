/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:31:18 by mvomiero          #+#    #+#             */
/*   Updated: 2023/04/10 13:25:48 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_data	*data;

	data = init_data(ac, av);
	if (!data)
		return (EXIT_FAILURE);
	if (!start_dinner(data))
		return(EXIT_FAILURE);
	stop_dinner(data);
	return(EXIT_SUCCESS);
}