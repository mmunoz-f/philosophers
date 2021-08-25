/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 12:49:35 by miguel            #+#    #+#             */
/*   Updated: 2021/08/24 19:21:52 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_forks(t_philo *table, t_plist *philosopher)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = &(table->forks[philosopher->n - 1]);
	if (philosopher->n == table->nphilo)
		fork2 = &(table->forks[0]);
	else
		fork2 = &(table->forks[philosopher->n]);
	if (philosopher->n % 2)
		pthread_mutex_lock(fork1);
	else
		pthread_mutex_lock(fork2);
	print_philo_msg(philosopher, M_FORK_MSG);
	if (philosopher->n % 2)
		pthread_mutex_lock(fork2);
	else
		pthread_mutex_lock(fork1);
	print_philo_msg(philosopher, M_FORK_MSG);
}

static void	leave_forks(t_philo *table, t_plist *philosopher)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	fork1 = &(table->forks[philosopher->n - 1]);
	if (philosopher->n == table->nphilo)
		fork2 = &(table->forks[0]);
	else
		fork2 = &(table->forks[philosopher->n]);
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

void	philo_life_cicle(t_philo *table, t_plist *philosopher)
{
	while (!table->death && table->finished_philo < table->nphilo)
	{
		take_forks(table, philosopher);
		if (table->death && table->finished_philo < table->nphilo)
			break ;
		print_philo_msg(philosopher, M_EAT_MSG);
		pthread_mutex_lock(&(philosopher->lifetime_lock));
		gettimeofday(&(philosopher->lifetime), 0);
		pthread_mutex_unlock(&(philosopher->lifetime_lock));
		if (++(philosopher->eat_times) == table->n_eat_times)
		{
			pthread_mutex_lock(&(table->eat_counter_lock));
			table->finished_philo++;
			pthread_mutex_unlock(&(table->eat_counter_lock));
		}
		true_sleep(table->time_to_eat, table);
		leave_forks(table, philosopher);
		if (table->death && table->finished_philo < table->nphilo)
			break ;
		print_philo_msg(philosopher, M_SLEEP_MSG);
		true_sleep(table->time_to_sleep, table);
		print_philo_msg(philosopher, M_THINK_MSG);
	}
}

void	*philo_routine(void *pointer)
{
	t_plist	*philosopher;
	t_philo	*table;

	philosopher = pointer;
	table = philosopher->table;
	pthread_mutex_init(&(philosopher->lifetime_lock), 0);
	philo_life_cicle(table, philosopher);
	leave_forks(table, philosopher);
	return (0);
}
