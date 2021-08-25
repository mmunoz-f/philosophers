/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 13:37:54 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 15:12:09 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include "plists/plists.h"

/* philosopher action messages */
# define M_FORK_MSG "has taken a fork"
# define M_EAT_MSG "is eating"
# define M_SLEEP_MSG "is sleeping"
# define M_THINK_MSG "is thinking"
# define M_DIE_MSG "died"

typedef struct s_philo
{
	int				nphilo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat_times;
	t_plist			*philosophers;
	pthread_mutex_t	*forks;
	struct timeval	start_time;
	pthread_mutex_t	print_lock;
	bool			death;
	pthread_mutex_t	eat_counter_lock;
	int				finished_philo;
}	t_philo;

/**
 * 	philo_utils.c
 */

int		ft_atoi(const char *nptr);

void	print_philo_msg(t_plist *philosopher, char *str);

void	true_sleep(int n, t_philo *table);

char	*ft_strchr(const char *s, int c);

/**
 *	philosophers.c
 */

void	*philo_routine(void *pointer);

/**
 * 	init_simulation.c
 */

int		start_philo_simulation(t_philo *philo);

#endif
