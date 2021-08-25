/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plists.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:13:06 by miguel            #+#    #+#             */
/*   Updated: 2021/08/19 21:21:50 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plists.h"

t_plist	*new_philo(int n)
{
	t_plist	*philo;

	philo = malloc(sizeof(t_plist));
	if (!philo)
		return (0);
	philo->n = n;
	philo->next = 0;
	philo->eat_times = 0;
	return (philo);
}

t_plist	*plst_last(t_plist *plist)
{
	while (plist && plist->next)
		plist = plist->next;
	return (plist);
}

void	plst_addback(t_plist **plist, t_plist *new_philo)
{
	t_plist	*plast;

	plast = plst_last(*plist);
	if (*plist)
		plast->next = new_philo;
	else
		*plist = new_philo;
}

void	plst_clear(t_plist *plist, unsigned int nnodes)
{
	unsigned int	i;
	t_plist			*next;

	i = 0;
	while (i++ < nnodes)
	{
		next = plist->next;
		free(plist);
		plist = next;
	}
}
