/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:12:48 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/15 18:21:44 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*finish_monitor(void *arg)
{
	int		i;
	t_data	*data;

	data = arg;
	sem_wait(data->finish);
	i = 0;
	while (i < data->num_of_philo)
		kill(data->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	*monitor_each_must_eat(void *argv)
{
	t_data	*data;
	int		i;

	data = argv;
	i = 0;
	while (i++ < data->num_of_philo)
		sem_wait(data->num_of_eat_finish_philo);
	sem_post(data->finish);
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (1)
	{
		sem_wait(philo->check);
		sem_wait(philo->data->acting);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->data->time_to_die)
		{
			printf("%lld\t%d\t %s\n", \
				time_to_ms(now) - time_to_ms(philo->data->create_at), \
				philo->n + 1, "died");
			sem_post(philo->data->finish);
			return (NULL);
		}
		sem_post(philo->data->acting);
		sem_post(philo->check);
	}
	return (NULL);
}
