/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 13:09:49 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 15:02:40 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	true_sleep(int n, t_philo *table)
{
	struct timeval	tv_start;
	struct timeval	tv_now;

	gettimeofday(&tv_start, 0);
	while (!table->death && table->finished_philo < table->nphilo
		&& gettimeofday(&tv_now, 0) != -1
		&& (tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000) - (tv_start.tv_sec
			* 1000 + tv_start.tv_usec / 1000) < n)
		usleep(50);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	print_philo_msg(t_plist *philosopher, char *str)
{
	struct timeval	tv_now;
	t_philo			*table;

	table = philosopher->table;
	pthread_mutex_lock(&(((t_philo *)philosopher->table)->print_lock));
	gettimeofday(&tv_now, 0);
	if (table->finished_philo < table->nphilo
		&& (!((t_philo *)philosopher->table)->death
			|| !ft_strcmp(str, M_DIE_MSG)))
		printf("%lu %i %s\n", (tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000)
			- (((t_philo *)philosopher->table)->start_time.tv_sec * 1000
				+ ((t_philo *)philosopher->table)->start_time.tv_usec / 1000),
			philosopher->n, str);
	pthread_mutex_unlock(&(((t_philo *)philosopher->table)->print_lock));
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	unsigned int	nbr;
	int				n;

	i = 0;
	nbr = 0;
	n = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] < 14 && nptr[i] > 8)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = 1;
		i++;
	}
	while (nptr[i] < 58 && nptr[i] > 47)
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	if (n == 0)
		return ((int)nbr);
	return (-(int)nbr);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}
