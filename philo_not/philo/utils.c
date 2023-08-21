/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealbayra <ealbayra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:15:26 by ealbayra          #+#    #+#             */
/*   Updated: 2023/08/11 23:28:42 by ealbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"
#include <unistd.h>

void	ft_sleep(uint64_t ms1)
{
	uint64_t	data;

	data = ms();
	while (1)
	{
		if (ms() - data >= ms1)
			break ;
		usleep(100);
	}
}

uint64_t	ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / (long)1000));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_only_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!ft_isdigit(argv[i][j]))
			return (1);
		while (ft_isdigit(argv[i][j]))
			j++;
		if (argv[i][j])
			return (1);
		i++;
	}
	return (0);
}

int	no_negative_atoi(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = -1;
	if (!str)
		return (0);
	while (*(str + ++i))
		res = (res * 10) + (*(str + i) - '0');
	return (res);
}
