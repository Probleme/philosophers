/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:08:41 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/15 16:13:08 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int			id;
	int			nbr_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_num;
	int			end;
	long int	time_to_start;
	long int	last_eat;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*eat;
}				t_philo;

typedef struct s_data
{
	int			nbr_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_num;
	int			end;
	long int	time_to_start;
	sem_t		*forks;
}				t_data;

#endif