/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 03:51:18 by miguel            #+#    #+#             */
/*   Updated: 2021/08/25 15:10:48 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	true_sleep(unsigned int n)
{
	struct timeval	tv_start;
	struct timeval	tv_now;

	gettimeofday(&tv_start, 0);
	while (gettimeofday(&tv_now, 0) != -1
		&& (tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000) - (tv_start.tv_sec
			* 1000 + tv_start.tv_usec / 1000) < n)
		usleep(50);
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

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	t;
	char	*a;

	i = 0;
	a = (char *)malloc(count * size);
	if (!a)
		return (0);
	t = count * size;
	while (i < t)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
