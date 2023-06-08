/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:14 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/08 13:44:01 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (print_error("Error gettting time of day\n", NULL));
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	print_msg(char *str, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->time_to_start;
	if (ft_strcmp("died", str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	dining(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	philo->dining = 1;
	philo->time_to_die = get_time() + philo->data->time_to_die;
	print_msg("is eating", philo);
	philo->dining_count++;
	ft_usleep(philo->data->time_to_eat);
	philo->dining = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_msg("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}
