/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:15:03 by ealbayra          #+#    #+#             */
/*   Updated: 2023/08/14 22:03:07 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	*start_philo(void *args) // thread sadece void* alabilen bir fonksiyonda calisiyor-her seyi alabilsin diye
{
	t_philo	*philo;

	philo = (t_philo *)args; // fonksiyona gelen void* arguman burada typecast'lenerek t_philo veri tipinde kullaniliyor
	if ((philo->philo_id + 1) % 2 == 0)
		ft_sleep(50);// hepsi ayni anda erismesin diye uyutuyor
	pthread_mutex_lock(&philo->table->data);
	while (philo->table->philo_dead)
	{
		pthread_mutex_unlock(&philo->table->data);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
		pthread_mutex_lock(&philo->table->data);
	}
	pthread_mutex_unlock(&philo->table->data);
	return (NULL);
}

void	*eat_control(void *args) // opsiyonel olarak yazilan arguman varsa yemeleri gereken sayi kadar yediler mi check
{
	t_table	*data;

	data = (t_table *)args;
	while (data->must_eat != -1) // 5.arguman varsa
	{
		pthread_mutex_lock(&data->_eat_control);
		if (data->number_of_philo == data->eat_control)
		{
			pthread_mutex_lock(&data->data);
			data->philo_dead = 0;
			pthread_mutex_unlock(&data->data);
			pthread_mutex_unlock(&data->_eat_control);
			break ;
		}
		pthread_mutex_unlock(&data->_eat_control);
	}
	return (NULL);
}

void	start_threads(t_table *data)
{
	int			i;
	pthread_t	x;
	pthread_t	y;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, // her bir philo'yu thread yapiyor
			start_philo, (void *)&data->philo[i]); // void * olarak adresini yolluyor
		i++;
	}
	pthread_create(&x, NULL, &die_control, data);
	pthread_create(&y, NULL, &eat_control, data);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (data->number_of_philo == 1)
			pthread_detach(data->philo[i].thread);
		else
			pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(x, NULL);
	pthread_join(y, NULL);
}

void	the_end(t_table *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->_last_eat);
	pthread_mutex_destroy(&data->data);
	pthread_mutex_destroy(&data->_eat_control);
	while (++i < data->number_of_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free(data->fork);
	free(data->philo);
	free(data);
}
