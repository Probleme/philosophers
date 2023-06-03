/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:21 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/03 19:32:02 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	alloc_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(t_data) * (data->num_philo));
	if (!data->philo)
		return (1);
	while (i < data->num_philo)
	{
		data->philo[i].eat_count = 0;
		data->philo[i].last_eat_time = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = i + 1;
		data->philo[i].data = data;
		data->philo[i].id_philo = i + 1;
		if (i != 0 && i + 1 == data->num_philo)
			data->philo[i].right_fork = 0;
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->print), NULL))
		return (print_error("Error\nprint mutex init failed"));
	if (pthread_mutex_init(&(data->search_fork), NULL))
		return (print_error("Error\nsearch_fork mutex init failed"));
	if (pthread_mutex_init(&(data->eat), NULL))
		return (print_error("Error\neat mutex init failed"));
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->num_philo));
	if (!data->forks)
		return (print_error("Error\nmalloc forks failed"));
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (print_error("Error\nforks mutex init failed"));
		i++;
	}
	return (0);
}

int	init_philo(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_num = -1;
	if (argc == 6)
		data->must_eat_num = ft_atoi(argv[5]);
	if (data->must_eat_num == 0)
		return (print_error("0 ms	all philo eat 0 time"));
	data->fork_st = malloc(sizeof(int) * data->num_philo);
	if (!data->fork_st)
		return (print_error("Error\nmalloc failed fork"));
	while (i < data->num_philo)
		data->fork_st[i++] = 0;
	data->is_all_safe = 1;
	if (alloc_philo(data))
		return (print_error("Error\nmalloc failed philo"));
	if (init_forks(data))
		return (1);
	return (0);
}
