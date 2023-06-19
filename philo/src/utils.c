/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:13:59 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/19 20:05:36 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atoi(const char *str)
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

int	ft_isnumeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_get_time_ms(size_t start)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_usec / 1000 + time.tv_sec * 1000 - start);
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

void	ft_usleep(size_t time)
{
	size_t    start;

    start = ft_get_time_ms(0);
    while ((ft_get_time_ms(0) - start) < time)
        usleep(100);
}
