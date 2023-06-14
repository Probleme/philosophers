/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:21 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/14 15:59:24 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	r;
	int					s;

	i = 0;
	r = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	return (r * s);
}

void	ft_init_philo(t_philo *philo, t_data *data, int id)
{
	philo->id = id;
	philo->t_last_meal = 0;
	philo->t_last_act = 0;
	philo->first_fork = (id + id % 2) % data->philo_nbr;
	philo->second_fork = (id + 1 - id % 2) % data->philo_nbr;
	philo->data = data;
	philo->must_eat_num = data->must_eat_num;
	philo->time_to_start = data->time_to_start;
	philo->mutex = &data->philo_mutex[id];
	philo->time = 0;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->time_to_die = data->time_to_die;
	philo->time_to_think = (philo->time_to_die - philo->time_to_eat - philo->time_to_sleep) / 2;
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
	data->plates = 0;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 1 || data->time_to_eat < 1 || data->time_to_sleep < 1)
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
	data->philo_nbr = ft_atoi(argv[1]);
	if (data->philo_nbr == 0)
		return (ft_error("Invalid number of philos at least one philo\n", data));
	if (ft_init_data(data, argc, argv))
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * (data->philo_nbr));
	data->philo_mutex = malloc(sizeof(pthread_mutex_t) * (data->philo_nbr));
	if (!data->philo || !data->forks_mutex || !data->philo_mutex)
		ft_error("Memory allocation failed\n", data);
	data->time_to_start = ft_get_time_ms(0);
	if (ft_init_mutex(data))
		return (1);
	return (0);
}
