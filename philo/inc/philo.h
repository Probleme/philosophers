/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:38:45 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/03 19:39:24 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id_philo;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long long		last_eat_time;
	pthread_t		tid;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	int				is_all_safe;
	int				*fork_st;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	search_fork;
}				t_data;

int			ft_atoi(const char *str);
int			print_error(char *str);
void		print_msg(t_data *data, t_philo *philo, char *str);

int			init_philo(int argc, char **argv, t_data *data);

long long	ft_get_time(void);
void		ft_wait(t_data *data, int time);

int			begin_philo(t_data *data, t_philo *philo);
void		check_philo_died(t_data *data);
void		clear_thread(t_data *data);
int			check_must_eat(t_data *p);
int			check_eat_time(t_data *p);

void		*do_philo(void *philo);

#endif
