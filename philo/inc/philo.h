/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:38:45 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/08 10:59:32 by ataouaf          ###   ########.fr       */
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
	int				id;
	pthread_t		t1;
	int				dining_count;
	int				status;
	int				dining;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_t		*id_thread;
	int				num_philo;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		time_to_start;
	int				eat_num;
	int				dead;
	int				finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	t_philo			*philosophers;
}					t_data;

int					check_input(int argc, char **argv, t_data *data);
int					ft_atoi(const char *str);
int					print_error(char *str, t_data *data);
int					check_num(int argc, char **argv, t_data *data);
int					init_pthreads(t_data *data);
int					init_philosophers(t_data *data);
int					init_forks(t_data *data);
uint64_t			get_time(void);
int					ft_strcmp(char *s1, char *s2);
void				print_msg(char *str, t_philo *philo);
int					ft_usleep(useconds_t time);
void				dining(t_philo *philo);
void				*manage(void *philos);
void				ft_exit(t_data *data);
int					init_threads(t_data *data);
void				*mythread(void *philos);

#endif