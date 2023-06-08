/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:35:27 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/08 10:56:53 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	one_philo(t_data *data)
{
	data->time_to_start = get_time();
	if (pthread_create(&data->id_thread[0], NULL, &mythread,
			&data->philosophers[0]))
		return (print_error("Error create thread", data));
	pthread_detach(data->id_thread[0]);
	while (data->dead == 0)
		ft_usleep(0);
	ft_exit(data);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_input(argc, argv, &data))
		return (1);
	if (check_num(argc, argv, &data))
		return (1);
	if (init_pthreads(&data) != 0)
		return (1);
	if (init_forks(&data) != 0)
		return (print_error("Error init forks\n", &data));
	if (init_philosophers(&data) != 0)
		return (print_error("Error init philos\n", &data));
	if (data.num_philo == 1)
		return (one_philo(&data));
	if (init_threads(&data))
		return 1;
	ft_exit(&data);
	return (0);
}
