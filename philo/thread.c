/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:04 by ataouaf           #+#    #+#             */
/*   Updated: 2023/05/24 17:47:24 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manage(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->dining == 0)
			print_msg("died",&philo->lock);
		if (philo->dining_count == philo->data->eat_num)
		{
			pthread_mutex_lock(&philo->lock);
			philo->data->finish++;
			philo->dining_count++;
			pthread_mutex_unlock(&philo->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*mythread(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	philo->time_to_die = philo->data->time_to_die + get_time();
	if (pthread_create(&philo->t1, NULL, &manage, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		dining(philo);
		print_msg("is thinking", philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}
