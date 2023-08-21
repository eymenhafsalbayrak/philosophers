/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:15:18 by ealbayra          #+#    #+#             */
/*   Updated: 2023/08/14 21:51:40 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork[philo->r_fork]);
	pthread_mutex_lock(&philo->table->fork[philo->l_fork]);
	pthread_mutex_lock(&philo->table->write);
	if (philo->_must_eat_c != philo->table->must_eat //????
		&& philo->table->philo_dead == 1)
	{
		printf("%llu %d has taken a fork \n", ms() - philo->table->start, // su anki zamandan basta aldigim zamani cikartiyorum??
			philo->philo_id + 1); // catali alan philo'nun id'si
		printf("%llu %d is eating\n", ms() - philo->table->start, // yedigi sure?
			philo->philo_id + 1);
	}
	pthread_mutex_unlock(&philo->table->write);
	philo->_must_eat_c++;
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->_last_eat);
	philo->last_eat = ms();
	pthread_mutex_unlock(&philo->table->_last_eat);
	pthread_mutex_unlock(&philo->table->fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->table->fork[philo->l_fork]);
	if (philo->_must_eat_c == philo->table->must_eat)
	{
		pthread_mutex_lock(&philo->table->_eat_control);
		philo->table->eat_control++;
		pthread_mutex_unlock(&philo->table->_eat_control);
	}
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write);
	pthread_mutex_lock(&philo->table->data);
	if (philo->_must_eat_c != philo->table->must_eat
		&& philo->table->philo_dead == 1)
		printf("%llu %d is sleeping\n", ms() - philo->table->start,
			philo->philo_id + 1);
	pthread_mutex_unlock(&philo->table->write);
	pthread_mutex_unlock(&philo->table->data);
	ft_sleep(philo->table->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write);
	pthread_mutex_lock(&philo->table->data);
	if (philo->_must_eat_c != philo->table->must_eat
		&& philo->table->philo_dead == 1)
		printf("%llu %d is thinking\n", ms() - philo->table->start,
			philo->philo_id + 1);
	pthread_mutex_unlock(&philo->table->data);
	pthread_mutex_unlock(&philo->table->write);
}
