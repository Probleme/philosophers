/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:14 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/03 19:44:45 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	is_thinking(t_philo *philo, t_data *data)
{
	if (data->is_all_safe == 0)
		data->is_all_safe = 0;
	else
		print_msg(data, philo, "is thinking");
}

void	is_sleeping(t_philo *philo, t_data *data)
{
	if (data->is_all_safe == 0)
		data->is_all_safe = 0;
	else
	{
		print_msg(data, philo, "is sleeping");
		ft_wait(data, data->time_to_sleep);
	}
}

void	is_eating(t_philo *philo, t_data *data)
{
	long long	time;

	if (data->is_all_safe == 0)
		time = 0;
	else
	{
		pthread_mutex_lock(&(data->eat));
		time = ft_get_time() - data->start_time;
		philo->last_eat_time = time;
		print_msg(data, philo, "is eating");
		pthread_mutex_unlock(&(data->eat));
	}
}

int	get_fork(t_philo *p, t_data *data)
{
	if (data->is_all_safe == 0)
		return (0);
	pthread_mutex_lock(&data->search_fork);
	if (data->fork_st[p->left_fork] == 0 && data->fork_st[p->right_fork] == 0)
	{
		pthread_mutex_lock(&data->forks[p->left_fork]);
		print_msg(data, p, "has taken a fork");
		data->fork_st[p->left_fork] = 1;
		pthread_mutex_lock(&data->forks[p->right_fork]);
		print_msg(data, p, "has taken a fork");
		data->fork_st[p->right_fork] = 1;
		is_eating(p, data);
		pthread_mutex_unlock(&data->search_fork);
		ft_wait(data, data->time_to_eat);
		data->fork_st[p->left_fork] = 0;
		data->fork_st[p->right_fork] = 0;
		pthread_mutex_unlock(&data->forks[p->left_fork]);
		pthread_mutex_unlock(&data->forks[p->right_fork]);
		p->eat_count++;
		return (0);
	}
	pthread_mutex_unlock(&data->search_fork);
	return (1);
}

void	*do_philo(void *philo_ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_ptr;
	data = philo->data;
	if (philo->id_philo % 2 != 1)
		ft_wait(data, data->time_to_eat);
	if (data->num_philo == 1)
	{
		pthread_mutex_lock(&data->forks[0]);
		print_msg(data, philo, "has taken a fork");
		ft_wait(data, data->time_to_die);
		pthread_mutex_unlock(&data->forks[0]);
		return (0);
	}
	while (data->is_all_safe)
	{
		while (get_fork(philo, data))
			usleep(100);
		is_sleeping(philo, data);
		is_thinking(philo, data);
		usleep(500);
	}
	return (0);
}
