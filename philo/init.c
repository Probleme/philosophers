/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:21 by ataouaf           #+#    #+#             */
/*   Updated: 2023/05/29 12:01:12 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philosophers[i].data = data;
		data->philosophers[i].id = i + 1;
		data->philosophers[i].time_to_die = data->time_to_die;
		data->philosophers[i].dining_count = 0;
		data->philosophers[i].dining = 0;
		data->philosophers[i].status = 0;
		pthread_mutex_init(&data->philosophers[i].lock, NULL);
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->philosophers[0].right_fork = &data->forks[data->num_philo - 1];
	data->philosophers[0].left_fork = &data->forks[0];
	i = 1;
	while (i < data->num_philo)
	{
		data->philosophers[i].right_fork = &data->forks[i - 1];
		data->philosophers[i].left_fork = &data->forks[i];
		i++;
	}
	return (0);
}

int	init_pthreads(t_data *data)
{
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->id_thread = malloc(sizeof(pthread_t) * data->num_philo);
	if (!data->id_thread)
		return (print_error("Error allocation threads", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (print_error("Error allocation forks", data));
	data->philosophers = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philosophers)
		return (print_error("Error allocation philos", data));
	return (0);
}
