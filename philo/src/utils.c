/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:13:59 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/15 14:34:20 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long int	ft_get_time_ms(long int start)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (0);
	return (t.tv_usec / 1000 + t.tv_sec * 1000 - start);
}

int	print_status(t_philo *philo, char *str)
{
	int	end;

	pthread_mutex_lock(&philo->data->is_safe);
	end = philo->data->end;
	if (!end)
		printf("%ld ms %d%s", ft_get_time_ms(philo->time_to_start), philo->id
			+ 1, str);
	pthread_mutex_unlock(&philo->data->is_safe);
	return (end);
}

int	ft_isnumeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_usleep(t_philo *philo, int time)
{
	int	end;

	end = 0;
	while ((ft_get_time_ms(philo->time_to_start) < time + philo->t_last_act
			- 1))
	{
		pthread_mutex_lock(&philo->data->is_safe);
		end = philo->data->end;
		pthread_mutex_unlock(&philo->data->is_safe);
		if (end)
			break ;
		usleep(100);
	}
	if (!end)
		while ((ft_get_time_ms(philo->time_to_start) < time
				+ philo->t_last_act))
			usleep(100);
}
