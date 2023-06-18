/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:35:27 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/18 16:03:23 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_free(t_data *data)
{
	if (data)
	{
		if (data->forks_mutex)
			free(data->forks_mutex);
		if (data->philo_mutex)
			free(data->philo_mutex);
		if (data->philo)
			free(data->philo);
		free(data);
		data = NULL;
	}
}

int	ft_error(char *err_msg, t_data *data)
{
	printf("%s", err_msg);
	ft_free(data);
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (ft_error(INVALID_ARGS, NULL));
	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isnumeric(argv[i][j++]))
				return (ft_error("Error\nOnly numbers between 0 and 9\n", NULL));
			if (ft_atoi(argv[i]) > MAX_INT)
				return (ft_error("Error\n Number is too big\n", NULL));
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_args(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (ft_init(data, argc, argv) != 0)
		return (1);
	if (begin_philo(data))
		return (1);
	ft_free(data);
	return (0);
}
