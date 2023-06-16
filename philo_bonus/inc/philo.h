/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:03:38 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/15 18:17:17 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

# define FT_ERROR		1
# define FT_SUCCESS		0

typedef struct s_philo
{
	int				n;
	int				num_of_eat;
	char			*name;
	sem_t			*check;
	pid_t			pid;
	struct s_data	*data;
	struct timeval	last_time_to_eat;

}					t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	sem_t			*acting;
	sem_t			*num_of_eat_finish_philo;
	sem_t			*finish;
	sem_t			*forks;
	t_philo			*philos;
	struct timeval	create_at;
}			t_data;

int			init(t_data *info, int argc, char *argv[]);
void		philo(t_philo *philo);
void		*monitor(void *argv);
void		*finish_monitor(void *arg);
void		*monitor_each_must_eat(void *argv);

int			ft_atoi(const char *nptr);
int			ft_puterror(char *str);
int			ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void		print_philo_msg(t_philo *philo, char *str);
char		*make_n_name(char *name, int n);

#endif
