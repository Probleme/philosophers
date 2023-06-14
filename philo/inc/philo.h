/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:38:45 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/14 15:44:33 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INVALID_ARGS "Invalid arguments.Try:\n \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philo
{
	int				id;
	int				t_last_meal;
	long int		time_to_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat_num;
	int				t_last_act;
	int				time;
	int				first_fork;
	int				second_fork;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	*mutex;
}					t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	int				end;
	int				plates;
	long int		time_to_start;
	t_philo			*philo;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*philo_mutex;
	pthread_mutex_t	is_safe;
}					t_data;

int					ft_init(t_data *data, int argc, char **argv);
void				begin_philo(t_data *data);
void				*routine(void *philo_ptr);
int					ft_error(char *err_msg, t_data *data);
int					is_died(t_philo *philo);
long int			ft_get_time_ms(long int start);
int					ft_isnumeric(char c);
int					print_status(t_philo *philo, char *str);
void				ft_usleep(t_philo *philo, int time);

#endif
