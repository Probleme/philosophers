/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:04 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/08 10:56:56 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*manage(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->dining == 0)
			print_msg("died", philo);
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

void	*monitoring(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %d", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finish >= philo->data->num_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	thread;

	i = 0;
	data->time_to_start = get_time();
	if (data->eat_num > 0)
	{
		if (pthread_create(&thread, NULL, &monitoring, &data->philosophers[0]))
			return (print_error("Error create threads", data));
	}
	while (i < data->num_philo)
	{
		if (pthread_create(&data->id_thread[i], NULL, &mythread, &data->philosophers[i]))
			return (print_error("Error create threads", data));
		ft_usleep(1);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(data->id_thread[i], NULL))
			return (print_error("Error joining threads", data));
		i++;
	}
	return (0);
}
