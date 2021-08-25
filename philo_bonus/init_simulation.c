/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 02:59:05 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 16:46:18 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	exit_bonus(t_philo *philo, int ret)
{
	unsigned int	i;

	sem_close(philo->fork_sem);
	sem_close(philo->print_sem);
	if (ret == 1)
	{
		printf("Error\ngettime function failed\n");
		exit(ret);
	}
	if (philo->pids)
	{
		i = 0;
		while (i < philo->nphilo)
		{
			if (philo->pids[i])
				kill(philo->pids[i], SIGKILL);
			i++;
		}
		if (ret)
			printf("Error\nFork failed\n");
	}
	else if (ret)
		printf("Error\nMalloc failed\n");
	exit(ret);
}

static int	create_philo_processes(t_philo *philo)
{
	unsigned int	i;

	philo->pids = ft_calloc(sizeof(pid_t), philo->nphilo);
	if (!philo->pids)
		return (1);
	i = 0;
	while (i < philo->nphilo)
	{
		philo->pids[i] = fork();
		if (philo->pids[i] < 0)
			return (1);
		if (!philo->pids[i])
			birth_philosopher(philo, i + 1);
		i++;
	}
	return (0);
}

static void	*check_death(void *pointer)
{
	t_philo			*philo;
	int				status;
	unsigned int	i;

	philo = pointer;
	waitpid(0, &status, 0);
	if (WIFEXITED(status))
		exit_bonus(philo, 0);
	i = 0;
	while (i < philo->nphilo)
	{
		waitpid(philo->pids[i], 0, 0);
		i++;
	}
	return (0);
}

static void	check_if_done(t_philo *philo)
{
	unsigned int	i;
	pthread_t		check_dead_thread;

	if (pthread_create(&check_dead_thread, 0, check_death, philo))
		exit(-1);
	if (philo->n_eat_times)
	{
		i = philo->nphilo;
		while (i--)
			sem_wait(philo->neat_times_sem);
		sem_wait(philo->print_sem);
		exit_bonus(philo, 0);
	}
	pthread_join(check_dead_thread, 0);
}

int	start_philo_simulation(t_philo *philo)
{
	if (gettimeofday(&(philo->start_time), 0))
		exit_bonus(philo, 1);
	if (create_philo_processes(philo))
		exit_bonus(philo, 2);
	check_if_done(philo);
	return (0);
}
