/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:13:56 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/08 10:56:50 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_input(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
    {
        printf("Invalid arguments.\nTry : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
        return (1);
    }
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
				j++;
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return print_error("Only positive numbers", data);
			j++;
		}
		i++;
	}
	return (0);
}

int check_num(int argc, char **argv, t_data *data)
{
	if (argc == 6)
		data->eat_num = (int)ft_atoi(argv[5]);
	else
		data->eat_num = -1;
	data->num_philo = (int)ft_atoi(argv[1]);
	data->time_to_die = (uint64_t)ft_atoi(argv[2]);
	data->time_to_eat = (uint64_t)ft_atoi(argv[3]);
	data->time_to_sleep = (uint64_t)ft_atoi(argv[4]);
	data->dead = 0;
	data->finish = 0;
	if (data->num_philo <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (print_error("Invalid Input", data));
	return (0);
}