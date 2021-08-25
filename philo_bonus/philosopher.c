/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:32:14 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/08/25 15:17:07 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	print_philo_msg(t_philosopher philosopher, char *str)
{
	struct timeval	tv_now;

	sem_wait(philosopher.print_sem);
	gettimeofday(&tv_now, 0);
	printf("%lu %i %s\n", (tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000)
		- (((t_philo *)philosopher.table)->start_time.tv_sec * 1000
			+ ((t_philo *)philosopher.table)->start_time.tv_usec / 1000),
		philosopher.n, str);
	if (ft_strcmp(str, M_DIE_MSG))
		sem_post(philosopher.print_sem);
}

static void	*check_lifetime(void *pointer)
{
	struct timeval	check_time;
	t_philo			*table;
	t_philosopher	*philosopher;

	philosopher = pointer;
	table = philosopher->table;
	while (1)
	{
		usleep(50);
		sem_wait(philosopher->lifetime_sem);
		gettimeofday(&check_time, 0);
		if ((check_time.tv_sec * 1000 + check_time.tv_usec / 1000)
			- (philosopher->lifetime.tv_sec * 1000
				+ philosopher->lifetime.tv_usec / 1000) > table->time_to_die)
		{
			print_philo_msg(*philosopher, M_DIE_MSG);
			exit(1);
		}
		sem_post(philosopher->lifetime_sem);
	}
	return (0);
}

static void	lets_eat(t_philo *philo, t_philosopher *philosopher)
{
	sem_wait(philosopher->forks_sem);
	print_philo_msg(*philosopher, M_FORK_MSG);
	sem_wait(philosopher->forks_sem);
	print_philo_msg(*philosopher, M_FORK_MSG);
	philosopher->eat_times++;
	if (philosopher->eat_times == ((t_philo *)philosopher->table)->n_eat_times)
		sem_post(philosopher->neat_times_sem);
	print_philo_msg(*philosopher, M_EAT_MSG);
	sem_wait(philosopher->lifetime_sem);
	gettimeofday(&(philosopher->lifetime), 0);
	sem_post(philosopher->lifetime_sem);
	true_sleep(philo->time_to_eat);
	sem_post(philosopher->forks_sem);
	sem_post(philosopher->forks_sem);
}

static void	init_philosopher(t_philo *philo, t_philosopher *philosopher,
	unsigned int n)
{
	philosopher->n = n;
	philosopher->table = philo;
	philosopher->eat_times = 0;
	philosopher->forks_sem = sem_open(M_FORKS_SEM, O_RDWR);
	if (philosopher->forks_sem == SEM_FAILED)
		exit(-1);
	philosopher->print_sem = sem_open(M_PRINT_SEM, O_RDWR);
	if (philosopher->print_sem == SEM_FAILED)
		exit(-1);
	philosopher->neat_times_sem = sem_open(M_NEAT_TIMES_SEM, O_RDWR);
	if (philosopher->neat_times_sem == SEM_FAILED)
		exit(-1);
	sem_unlink(M_LIFETIME_SEM);
	philosopher->lifetime_sem = sem_open(M_LIFETIME_SEM,
			O_CREAT | O_EXCL, 0777, 1);
	if (philosopher->lifetime_sem == SEM_FAILED)
		exit(-1);
}

void	birth_philosopher(t_philo *philo, unsigned int n)
{
	t_philosopher	philosopher;

	init_philosopher(philo, &philosopher, n);
	if (pthread_create(&(philosopher.pthread), 0, check_lifetime, &philosopher))
		exit(-1);
	philosopher.lifetime = philo->start_time;
	while (1)
	{
		lets_eat(philo, &philosopher);
		print_philo_msg(philosopher, M_SLEEP_MSG);
		true_sleep(philo->time_to_sleep);
		print_philo_msg(philosopher, M_THINK_MSG);
	}
	exit(0);
}
