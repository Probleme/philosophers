/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:14:04 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/14 11:02:38 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	join_thread(t_data *data, int i)
{
	pthread_mutex_lock(&data->is_safe);
	data->end = 1;
	pthread_mutex_unlock(&data->is_safe);
	while (i >= 0)
		pthread_join(data->philo[--i].thread, NULL);
}

int	check_is_died(t_data *data)
{
	int	i;
	int	end;

	end = 0;
	i = -1;
	while (!end && ++i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->philo_mutex[i]);
		if ((data->philo[i].t_last_meal + data->time_to_die)
			<= ft_get_time_ms(data->time_to_start))
		{
			end = 1;
			pthread_mutex_lock(&data->is_safe);
			data->end = end;
			printf("%ld ms %d%s", ft_get_time_ms(data->time_to_start),
				data->philo[i].id + 1, " died\n");
			pthread_mutex_unlock(&data->is_safe);
		}
		pthread_mutex_unlock(&data->philo_mutex[i]);
		pthread_mutex_lock(&data->is_safe);
		end = data->end;
		pthread_mutex_unlock(&data->is_safe);
	}
	return (end);
}

void	check_end(t_data *data)
{
	int	end;

	end = 0;
	while (!end)
	{
		if (check_is_died(data))
			break ;
		usleep(100);
	}
}

void	begin_philo(t_data *data)
{
	int		i;

	i = -1;
	pthread_mutex_lock(&data->is_safe);
	while (++i < data->philo_nbr)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				routine, (void *)(&data->philo[i])))
		{
			pthread_mutex_unlock(&data->is_safe);
			join_thread(data, i);
			ft_error("Thread creation ft_error\n", data);
		}
	}
	pthread_mutex_unlock(&data->is_safe);
	check_end(data);
	while (i > 0)
		pthread_join(data->philo[--i].thread, NULL);
}
