/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:38:45 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/19 16:44:42 by ataouaf          ###   ########.fr       */
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
# define MAX_INT 2147483647

typedef struct s_philo
{
	int				id;
	size_t			time_to_start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat_num;
	size_t			time_last_eat;
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
	int				all_eat;
	int				end;
	size_t			time_to_start;
	t_philo			*philo;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*philo_mutex;
	pthread_mutex_t	is_safe;
}					t_data;

int					ft_init(t_data *data, int argc, char **argv);
int					begin_philo(t_data *data);
void				*routine(void *philo_ptr);
int					ft_error(char *err_msg, t_data *data);
int					is_died(t_philo *philo);
size_t				ft_get_time_ms(size_t start);
int					ft_isnumeric(char c);
int					print_status(t_philo *philo, char *str);
void				ft_usleep(size_t time);
long				ft_atoi(const char *str);

#endif
