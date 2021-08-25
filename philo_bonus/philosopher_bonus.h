/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 02:52:36 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 15:12:45 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <errno.h>

/* philosopher action messages */
# define M_FORK_MSG "has taken a fork"
# define M_EAT_MSG "is eating"
# define M_SLEEP_MSG "is sleeping"
# define M_THINK_MSG "is thinking"
# define M_DIE_MSG "died"

/* semaphores nanes */
# define M_FORKS_SEM "/forks_sem"
# define M_PRINT_SEM "/print_sem"
# define M_LIFETIME_SEM "/lifetime_sem"
# define M_NEAT_TIMES_SEM "/neat_times_sem"

typedef struct s_philo
{
	unsigned int	nphilo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	n_eat_times;
	struct timeval	start_time;
	sem_t			*fork_sem;
	sem_t			*print_sem;
	sem_t			*neat_times_sem;
	pid_t			*pids;
}	t_philo;

typedef struct s_philosopher
{
	unsigned int	n;
	unsigned int	eat_times;
	struct timeval	lifetime;
	pthread_t		pthread;
	t_philo			*table;
	sem_t			*print_sem;
	sem_t			*forks_sem;
	sem_t			*lifetime_sem;
	sem_t			*neat_times_sem;
}	t_philosopher;

/**
 * 	init_simulation.c
 */

int		start_philo_simulation(t_philo *philo);

/**
 * 	philo_util.c
 */

char	*ft_strchr(const char *s, int c);

void	true_sleep(unsigned int n);

int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t count, size_t size);

int		ft_strcmp(const char *s1, const char *s2);

/**
 * 	philosopher.c
 */

void	birth_philosopher(t_philo *philo, unsigned int n);

void	print_philo_msg(t_philosopher philosopher, char *str);

#endif
