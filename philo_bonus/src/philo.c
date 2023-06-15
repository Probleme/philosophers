/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:08:12 by ataouaf           #+#    #+#             */
/*   Updated: 2023/06/15 16:09:54 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (ft_error("Error: bad arguments\n"));
    if (ft_init_data(&data, argc, argv) == -1)
        return (ft_error("Error: bad arguments\n"));
    if (ft_init_philo(&data) == -1)
        return (ft_error("Error: bad arguments\n"));
    if (ft_create_process(&data) == -1)
        return (ft_error("Error: bad arguments\n"));
    ft_destroy_process(&data);
    return (0);
}