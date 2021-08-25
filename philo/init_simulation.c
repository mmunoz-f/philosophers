/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 19:15:40 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/08/24 19:22:01 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	give_philo_live(t_philo *philo)
{
	int		i;
	t_plist	*philosopher;

	i = 0;
	if (gettimeofday(&(philo->start_time), 0))
		return (1);
	while (i++ < philo->nphilo)
	{
		philosopher = philo->philosophers;
		philosopher->table = (void *)philo;
		philosopher->lifetime = philo->start_time;
		if (pthread_create(&(philo->philosophers->thread_id), 0, philo_routine,
				philosopher))
			return (1);
		philo->philosophers = philo->philosophers->next;
	}
	return (0);
}

static int	check_if_dead(t_plist *philosopher, t_philo *table)
{
	struct timeval	check_time;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	usleep(50);
	pthread_mutex_lock(&(philosopher->lifetime_lock));
	if (gettimeofday(&check_time, 0))
		return (1);
	if ((check_time.tv_sec * 1000 + check_time.tv_usec / 1000)
		- (philosopher->lifetime.tv_sec * 1000
			+ philosopher->lifetime.tv_usec / 1000) > table->time_to_die)
	{
		table->death = true;
		print_philo_msg(philosopher, M_DIE_MSG);
		fork1 = &(table->forks[philosopher->n - 1]);
		if (philosopher->n == table->nphilo)
			fork2 = &(table->forks[0]);
		else
			fork2 = &(table->forks[philosopher->n]);
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
	}
	pthread_mutex_unlock(&(philosopher->lifetime_lock));
	return (0);
}

static void	clean_leave(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nphilo)
		pthread_mutex_destroy(&(philo->forks[i]));
	free(philo->forks);
	plst_clear(philo->philosophers, philo->nphilo);
	pthread_mutex_destroy(&(philo->print_lock));
}

int	start_philo_simulation(t_philo *philo)
{
	int	i;

	if (give_philo_live(philo))
		return (1);
	while (!philo->death && philo->finished_philo < philo->nphilo)
	{
		if (check_if_dead(philo->philosophers, philo))
			return (1);
		philo->philosophers = philo->philosophers->next;
	}
	i = 0;
	while (i++ < philo->nphilo)
	{
		pthread_join(philo->philosophers->thread_id, 0);
		philo->philosophers = philo->philosophers->next;
	}
	clean_leave(philo);
	return (0);
}
