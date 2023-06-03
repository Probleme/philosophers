/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:35:27 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/03 18:19:47 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i != argc)
	{
		if (is_numeric(argv[i]))
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1)
		return (1);
	if (ft_atoi(argv[2]) < 0)
		return (1);
	if (ft_atoi(argv[3]) < 0)
		return (1);
	if (ft_atoi(argv[4]) < 0)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0)
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (print_error("Error\nTry : number_of_philosophers \
			time_to_die time_to_eat time_to_sleep \
			[number_of_times_each_philosopher_must_eat]"));
	if (check_input(argc, argv))
		return (print_error("Error\nOnly positive numbers or \
			at least one philosopher"));
	if (init_philo(argc, argv, &data))
		return (1);
	if (begin_philo(&data, (&data)->philo))
		return (1);
	return (0);
}
