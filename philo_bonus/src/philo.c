/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:11:57 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/15 18:22:05 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	pickup_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_philo_msg(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_philo_msg(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->check);
	gettimeofday(&philo->last_time_to_eat, NULL);
	print_philo_msg(philo, "is eating");
	philo->num_of_eat += 1;
	if (philo->num_of_eat == philo->data->num_of_must_eat)
		sem_post(philo->data->num_of_eat_finish_philo);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sem_post(philo->check);
}

static void	sleeping(t_philo *philo)
{
	print_philo_msg(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	print_philo_msg(philo, "is thinking");
}

void	philo(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitor, philo);
	if (philo->n % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (1)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	exit(0);
}
