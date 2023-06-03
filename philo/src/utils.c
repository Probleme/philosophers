/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:13:59 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/02 18:09:06 by ataouaf          ###   ########.fr       */
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

int	print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

long long	ft_get_time(void)
{
	long long		sec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (sec);
}

void	ft_wait(t_data *data, int time)
{
	long long	now_time;
	long long	start_time;

	start_time = ft_get_time();
	while (data->is_all_safe)
	{
		now_time = ft_get_time();
		if (now_time - start_time >= time)
			break ;
		usleep(300);
	}
}

void	print_msg(t_data *data, t_philo *philo, char *str)
{
	long long	time;

	if (data->is_all_safe == 0)
		time = 0;
	else
	{
		pthread_mutex_lock(&data->print);
		if (data->is_all_safe != 0)
		{
			time = ft_get_time() - data->start_time;
			printf("%lld ms	%d	%s\n", time, philo->id_philo, str);
		}
		pthread_mutex_unlock(&data->print);
	}
}
