/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:14:45 by ealbayra          #+#    #+#             */
/*   Updated: 2023/08/14 21:51:40 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"
#include "stdlib.h"

pthread_mutex_t	*mutex_init(t_table *data)
{
	int				i;
	pthread_mutex_t	*tmp;

	i = 0;
	tmp = malloc(sizeof(pthread_mutex_t) * data->number_of_philo); //philo yani fork sayisi kadar yer acip tmp'e esitliyor
	if (!tmp)
	{
		free(data);
		return (NULL);
	}
	while (i < data->number_of_philo) // philo sayisina gelene kadar her fork icin mutex initliyor
	{
		pthread_mutex_init(&tmp[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write, NULL); // data'nin adresindeki write icin -yazdirma icin- mutex
	pthread_mutex_init(&data->data, NULL); // data icin mutex
	pthread_mutex_init(&data->_last_eat, NULL); // son yeme????
	pthread_mutex_init(&data->_eat_control, NULL); // yeme kontrolu icin mutex
	return (tmp); // yer acilan tmp'i -forklari- donduruyor
}

t_table	*table_init(int argc, char **argv)
{
	t_table	*data;

	if (check_only_number(argc, argv)) // girilen argumanin sayi olup olmadigi kontrolu
	{
		printf("Error! Only Number!");
		return (NULL);
	}
	data = malloc(sizeof(t_table)); // data icin t_table tipinde malloc ile yer aciliyor
	if (!data)
		return (NULL);
	data->number_of_philo = no_negative_atoi(argv[1]); // data degiskeniyle t_table structinin icindeki degiskenlere deger veriyor/initliyor
	data->time_to_die = no_negative_atoi(argv[2]); // olme suresi
	data->time_to_eat = no_negative_atoi(argv[3]); // yeme suresi
	data->time_to_sleep = no_negative_atoi(argv[4]); // uyuma suresi
	if (argv[5]) // eger opsiyonel olarak girilen 5. arguman varsa o degeri must_eat fonksiyonuna atiyor
		data->must_eat = no_negative_atoi(argv[5]);
	else
		data->must_eat = -1; // yoksa o degere -1 veriliyor
	data->fork = mutex_init(data); // philo sayisi kadar olan forklari yaratip data'nin icindeki fork degiskenine atiyor ve diger mutexleri initliyor
	data->philo_dead = 1;
	data->start = ms(); // su anki zamani aliyor
	data->eat_control = 0; // son arguman'in kontrolu
	return (data);
}

void	philo_init(t_table *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo); // masa infolarinin tutuldugu struct'in icindeki philo struct'ina t_philo tipinde philo sayisi kadar yer aciliyor
	if (!data->philo)
	{
		free(data->fork);
		free(data);
		return ;
	}
	while (i < data->number_of_philo) // butun philolar'in ozelliklerine value atama
	{
		data->philo[i].philo_id = i; // philo'nun id'sini belirleme
		data->philo[i].r_fork = i; // philolarin sag taraftaki catalari philo'nun id'si ile ayni
		data->philo[i].l_fork = (i + 1) % data->number_of_philo; 
		data->philo[i].table = data;
		data->philo[i]._must_eat_c = 0;
		data->philo[i].last_eat = ms(); // oldu mu kontrolu icin baslangic degeri/zamani veriyor
		i++;
	}
}
