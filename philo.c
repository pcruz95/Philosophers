/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcruz <pcruz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:54:11 by pcruz             #+#    #+#             */
/*   Updated: 2021/08/13 15:34:38 by pcruz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		ret;

	ret = 0;
	if ((ac != 5 && ac != 6) || (ft_check_and_init_args(av, &data)))
		return (ft_exit_error(NULL, 1, "Error arguments\n"));
	ret = ft_init(&data);
	if (ret)
		return (ret);
	if (gettimeofday(&data.tp, NULL))
		return (ft_exit_error(&data, 4, "Error program\n"));
	if (ft_creating_threads(&data))
		ft_exit_error(&data, 5, "Error pthread_control_create\n");
	while (!data.var_death)
		usleep(10);
	return (ft_waiting_threads(&data));
}

int	ft_check_and_init_args(char **av, t_data *data)
{
	int				i;
	int				c;
	unsigned int	x;
	long			num;

	i = 0;
	c = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i], &num))
			return (1);
		x = 0;
		while (x < (unsigned int)(sizeof(unsigned int)))
			((unsigned char *)data)[c++] = ((unsigned char *)&num)[x++];
		if (i == 5)
			while (x++ < (unsigned int)(sizeof(long)))
				((unsigned char *)data)[c++] = 0;
	}
	if (i == 5)
		data->num_meals = -1;
	if (!data->num_philos || !data->time_to_die || \
		!data->time_to_eat || !data->time_to_sleep || \
		!data->num_meals)
		return (1);
	return (0);
}

int	ft_init(t_data *data)
{
	unsigned int	i;

	data->var_death = 0;
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->last_meal = malloc(sizeof(unsigned int) * data->num_philos);
	data->num_meals_array = malloc(sizeof(long int) * data->num_philos);
	data->thread_philo = malloc(sizeof(pthread_t) * data->num_philos);
	data->thread_control = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->mutex_forks || !data->last_meal || !data->num_meals_array || \
		!data->thread_philo || !data->thread_control)
		return (ft_exit_error(data, 2, "Error malloc\n"));
	if (pthread_mutex_init(&data->mutex_death, NULL) || \
		pthread_mutex_init(&data->mutex_print, NULL))
		return (ft_exit_error(data, 3, "Error pthread_mutex_init\n"));
	i = 0;
	while (i < data->num_philos)
		if (pthread_mutex_init(&data->mutex_forks[i++], NULL))
			return (ft_exit_error(data, 3, "Error pthread_mutex_init\n"));
	return (0);
}

int	ft_creating_threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->num_philos && i < MAX_N_THREADS / 2)
	{
		data->index_philo = i;
		data->last_meal[i] = 0;
		data->num_meals_array[i] = data->num_meals;
		if (pthread_create(&(data->thread_philo[i]), NULL, \
			ft_routine, (void *)data))
			return (1);
		if (pthread_create(&(data->thread_control[i]), NULL, \
			ft_control, (void *)data))
			return (1);
		i++;
		usleep(100);
	}
	return (0);
}

int	ft_waiting_threads(t_data *data)
{
	unsigned int	i;
	int				*status;
	int				ret;

	i = 0;
	ret = 0;
	while (i < data->num_philos && i < MAX_N_THREADS / 2)
	{
		if (pthread_join(data->thread_philo[i], (void *)&status))
			return (ft_exit_error(data, 6, "Error pthread_join\n"));
		if (status && *status)
		{
			ret = *status;
			free(status);
		}
		if (pthread_join(data->thread_control[i], (void *)&status))
			return (ft_exit_error(data, 6, "Error pthread_join\n"));
		if (status && *status)
		{
			ret = *status;
			free(status);
		}
		i++;
	}
	return (ft_exit(data, ret));
}
