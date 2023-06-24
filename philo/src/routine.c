/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:14 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/24 21:20:53 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_died(t_philo *philo)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&philo->data->is_safe);
	end = philo->data->end;
	pthread_mutex_unlock(&philo->data->is_safe);
	return (end);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_mutex[philo->first_fork]);
	pthread_mutex_lock(&philo->data->forks_mutex[philo->second_fork]);
	print_status(philo, " has taken a fork 1\n");
	print_status(philo, " has taken a fork 2\n");
	print_status(philo, " is eating\n");
	pthread_mutex_lock(philo->mutex);
	philo->time_last_eat = ft_get_time_ms(philo->time_to_start);
	pthread_mutex_unlock(philo->mutex);
	philo->must_eat_num--;
	if (philo->must_eat_num > -1)
	{
		pthread_mutex_lock(&philo->data->is_safe);
		if (++philo->data->all_eat == philo->data->must_eat_num
			* philo->data->philo_nbr)
			philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->is_safe);
	}
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->second_fork]);
	pthread_mutex_unlock(&philo->data->forks_mutex[philo->first_fork]);
}

void	is_sleeping(t_philo *philo)
{
	print_status(philo, " is sleeping\n");
	ft_usleep(philo->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	print_status(philo, " is thinking\n");
	ft_usleep(philo->time_to_think);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	int		end;

	end = 0;
	philo = (t_philo *)philo_ptr;
	if (philo->data->philo_nbr == 1)
	{
		print_status(philo, " has taken a fork\n");
		ft_usleep(philo->time_to_die + 1);
		end = is_died(philo);
	}
	if (philo->id % 2)
		ft_usleep(philo->time_to_eat);
	while (!end)
	{
		take_forks(philo);
		is_sleeping(philo);
		is_thinking(philo);
		end = is_died(philo);
	}
	return (0);
}
