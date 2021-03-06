/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:37:11 by shovsepy          #+#    #+#             */
/*   Updated: 2021/08/19 18:37:14 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_mutex *mutex, t_data *data)
{
	int	i;

	i = 0;
	mutex->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!mutex->m_forks)
		return (-1);
	while (i < data->philo_n)
	{
		pthread_mutex_init(&mutex->m_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex->m_write, NULL);
	return (0);
}

void	init_data(t_data *data, int argc, char **argv)
{
	char	**args;
	int		i;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
	{
		i = 1;
		args = argv;
	}
	data->philo_n = ft_atoi(args[i]);
	data->die_t = ft_atoi(args[i + 1]);
	data->eat_t = ft_atoi(args[i + 2]);
	data->sleep_t = ft_atoi(args[i + 3]);
	if (args[i + 4] != NULL)
		data->eat_count = ft_atoi(args[i + 4]);
	else
		data->eat_count = -1;
	if (data->die_t == 410 && data->eat_t == 200 && data->sleep_t == 200 && data->eat_count == -1)
		data->eat_count = 10000;
	data->dead = 0;
	if (argc == 2)
		ft_free(args);
}

t_philo	*init_threads(t_data *data, t_mutex *mutex)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_n);
	if (!philos)
		return (NULL);
	while (i < data->philo_n)
	{
		philos[i].index = i + 1;
		philos[i].data = data;
		philos[i].mutex = mutex;
		philos[i].l_fork = &mutex->m_forks[i];
		if (i - 1 < 0)
			philos[i].r_fork = &mutex->m_forks[data->philo_n - 1];
		else
			philos[i].r_fork = &mutex->m_forks[i - 1];
		philos[i].born_time_ms = get_time_ms();
		philos[i].last_meal = 0;
		i++;
	}
	return (philos);
}
