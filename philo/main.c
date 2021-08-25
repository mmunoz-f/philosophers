/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 13:35:25 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 15:07:00 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_valid_input(int argc, char **argv)
{
	int		i;
	char	*str;

	i = 0;
	while (++i < argc)
	{
		str = argv[i];
		while (*str)
		{
			if (!ft_strchr("0123456789", *str))
				return (1);
			str++;
		}
	}
	return (0);
}

static int	parse_argv(t_philo *philo, int argc, char **argv)
{
	if (check_valid_input(argc, argv))
		return (1);
	philo->nphilo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->n_eat_times = ft_atoi(argv[5]);
	if (philo->nphilo > 300 || philo->nphilo < 1 || philo->time_to_die > 60000
		|| philo->time_to_die < 1 || philo->time_to_eat > 60000
		|| philo->time_to_eat < 1 || philo->time_to_sleep > 60000
		|| philo->time_to_sleep < 1)
		return (1);
	if (argc == 6 && philo->n_eat_times < 1)
		return (1);
	else if (argc != 6)
		philo->n_eat_times = 0;
	return (0);
}

static int	init_philo(t_philo *philo, int argc, char **argv)
{
	int	i;

	if (parse_argv(philo, argc, argv))
		return (1);
	philo->philosophers = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nphilo);
	if (!philo->forks)
		return (1);
	philo->forks = memset(philo->forks, 0,
			sizeof(pthread_mutex_t) * philo->nphilo);
	i = -1;
	while (++i < philo->nphilo)
	{
		if (pthread_mutex_init(&(philo->forks[i]), 0))
			return (1);
	}
	if (pthread_mutex_init(&(philo->print_lock), 0))
		return (1);
	philo->finished_philo = 0;
	if (pthread_mutex_init(&(philo->eat_counter_lock), 0))
		return (1);
	philo->death = false;
	return (0);
}

static int	charge_philosophers(t_philo *philo)
{
	int		i;
	t_plist	*philosopher;

	i = 1;
	while (i <= philo->nphilo)
	{
		philosopher = new_philo(i);
		if (!philosopher)
			return (1);
		plst_addback(&(philo->philosophers), philosopher);
		i++;
	}
	(plst_last(philo->philosophers))->next = philo->philosophers;
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nArguments\n");
		return (1);
	}
	if (init_philo(&philo, argc, argv))
	{
		printf("Error\nNot valid argument values\n");
		return (1);
	}
	if (charge_philosophers(&philo))
		return (1);
	return (start_philo_simulation(&philo));
}
