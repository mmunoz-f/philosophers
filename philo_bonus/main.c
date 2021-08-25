/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:55:06 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 17:45:14 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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

static int	open_semaphores(t_philo *philo)
{
	sem_unlink(M_FORKS_SEM);
	philo->fork_sem = sem_open(M_FORKS_SEM, O_CREAT | O_EXCL, 0777,
			((int)philo->nphilo));
	if (philo->fork_sem == SEM_FAILED)
		return (1);
	sem_unlink(M_PRINT_SEM);
	philo->print_sem = sem_open(M_PRINT_SEM, O_CREAT | O_EXCL, 0777, 1);
	if (philo->print_sem == SEM_FAILED)
		return (1);
	sem_unlink(M_NEAT_TIMES_SEM);
	philo->neat_times_sem = sem_open(M_NEAT_TIMES_SEM,
			O_CREAT | O_EXCL, 0777, 0);
	if (philo->neat_times_sem == SEM_FAILED)
		return (1);
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
	if (open_semaphores(philo))
		return (2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	int		ret_init;

	if (argc < 5 || argc > 6)
	{
		printf("Error\nArguments\n");
		return (1);
	}
	ret_init = parse_argv(&philo, argc, argv);
	if (ret_init == 1)
	{
		printf("Error\nNot valid argument values\n");
		return (1);
	}
	else if (ret_init == 2)
	{
		printf("Error\nSem error\n");
		return (2);
	}
	return (start_philo_simulation(&philo));
}
