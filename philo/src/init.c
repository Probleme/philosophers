/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:21 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/19 20:11:00 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_init_philo(t_philo *philo, t_data *data, int id)
{
	philo->id = id;
	philo->time_last_eat = 0;
	philo->first_fork = id ;
	philo->second_fork = (id + 1) % data->philo_nbr;
	philo->data = data;
	philo->must_eat_num = data->must_eat_num;
	philo->time_to_start = data->time_to_start;
	philo->mutex = &data->philo_mutex[id];
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->time_to_die = data->time_to_die;
	philo->time_to_think = (philo->time_to_die - philo->time_to_eat
			- philo->time_to_sleep) / 2;
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->is_safe, NULL))
		return (ft_error("Error Mutex initialization\n", data));
	i = -1;
	while (++i < data->philo_nbr)
		if (pthread_mutex_init(&data->forks_mutex[i], NULL)
			|| pthread_mutex_init(&data->philo_mutex[i], NULL))
			return (ft_error("Error Mutex initialization\n", data));
	i = -1;
	while (++i < data->philo_nbr)
		ft_init_philo(&data->philo[i], data, i);
	return (0);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->forks_mutex = NULL;
	data->philo_mutex = NULL;
	data->philo = NULL;
	data->end = 0;
	data->all_eat = 0;
	data->philo_nbr = ft_atoi(argv[1]);
	if (data->philo_nbr == 0)
		return (ft_error("Invalid number of philos at least one philo\n",
				data));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->time_to_start = ft_get_time_ms(0);
	if (data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (ft_error("Invalid time value\n", data));
	if (argc == 6)
	{
		data->must_eat_num = ft_atoi(argv[5]);
		if (data->must_eat_num < 1)
			return (ft_error("Invalid must eat value\n", data));
	}
	else
		data->must_eat_num = -1;
	return (0);
}

int	ft_init(t_data *data, int argc, char **argv)
{
	if (ft_init_data(data, argc, argv))
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (ft_error("Memory allocation failed\n", data));
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * (data->philo_nbr));
	if (!data->forks_mutex)
		return (ft_error("Memory allocation failed\n", data));
	data->philo_mutex = malloc(sizeof(pthread_mutex_t) * (data->philo_nbr));
	if (!data->philo_mutex)
		return (ft_error("Memory allocation failed\n", data));
	if (ft_init_mutex(data))
		return (1);
	return (0);
}
