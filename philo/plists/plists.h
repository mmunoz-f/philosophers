/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plists.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:10:18 by miguel            #+#    #+#             */
/*   Updated: 2021/08/19 21:22:52 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLISTS_H
# define PLISTS_H

# include <pthread.h>
# include <stdlib.h>

typedef struct s_plist
{
	int				n;
	pthread_t		thread_id;
	void			*table;
	struct timeval	lifetime;
	int				eat_times;
	pthread_mutex_t	lifetime_lock;
	struct s_plist	*next;
}	t_plist;

/**
 * 	plists.c
 */

t_plist	*new_philo(int n);

t_plist	*plst_last(t_plist *plist);

void	plst_addback(t_plist **plist, t_plist *new_philo);

void	plst_clear(t_plist *plist, unsigned int nnodes);

#endif
