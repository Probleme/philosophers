/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:04 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/03 19:46:59 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	begin_philo(t_data *data, t_philo *philo)
{
	int		i;
	void	*philo_v;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->num_philo)
	{
		philo_v = (void *)&(philo[i]);
		if (pthread_create(&(philo[i].tid), NULL, do_philo, philo_v) == -1)
			return (print_error("Error\nthread create failed"));
		i++;
	}
	ft_wait(data, data->time_to_eat);
	check_philo_died(data);
	return (0);
}

void	check_philo_died(t_data *data)
{
	while (data->is_all_safe)
	{
		pthread_mutex_lock(&(data->eat));
		if (check_eat_time(data))
			break ;
		if (data->must_eat_num != -1)
			if (check_must_eat(data))
				break ;
		pthread_mutex_unlock(&(data->eat));
		usleep(100);
	}
	pthread_mutex_unlock(&(data->eat));
	clear_thread(data);
}

int	check_eat_time(t_data *p)
{
	long long	time;
	int			i;

	i = 0;
	while (i < p->num_philo)
	{
		time = ft_get_time() - p->start_time;
		if ((time - p->philo[i].last_eat_time) > p->time_to_die)
		{
			pthread_mutex_lock(&p->print);
			p->is_all_safe = 0;
			printf("%lld ms	%d	is died\n", time, p->philo[i].id_philo);
			pthread_mutex_unlock(&p->print);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_must_eat(t_data *data)
{
	long long	time;
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (i < data->num_philo)
	{
		if (data->philo[i].eat_count >= data->must_eat_num && data->must_eat_num != -1)
			check++;
		i++;
	}
	if (check == data->num_philo)
	{
		pthread_mutex_lock(&data->print);
		data->is_all_safe = 0;
		time = ft_get_time() - data->start_time;
		printf("%lldms	all philo eat %d time\n", time, data->must_eat_num);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}

void	clear_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(data->forks);
	free(data->philo);
	free(data->fork_st);
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&(data->eat));
	pthread_mutex_destroy(&(data->search_fork));
}
