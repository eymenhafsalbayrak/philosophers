/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:14:28 by ealbayra          #+#    #+#             */
/*   Updated: 2023/08/14 21:39:26 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "stdio.h"

int	main(int argc, char **argv)
{
	t_table	*data; // t_table tipinde degisken tanimlama

	if ((argc < 5) || (argc > 6)) // kac arguman girilmeli
	{
		printf("Arguments Error!");
		return (0);
	}
	data = table_init(argc, argv); // disardan aldigi degerleri table_init fonksiyonuna gonderip data degiskenine atiyor
	if (!data) // data var mi kontrol
		return (0);
	philo_init(data);// data'yi philo_init fonks gonderiyor
	start_threads(data);
	the_end(data);
}
