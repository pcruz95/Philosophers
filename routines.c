/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcruz <pcruz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:15:10 by pcruz             #+#    #+#             */
/*   Updated: 2021/10/07 12:16:57 by pcruz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_data			*data;
	unsigned int	c;
	unsigned int	d;

	data = (t_data *)arg;
	c = data->index_philo;
	d = c - 1;
	if (c == 0)
		d = data->num_philos - 1;
	while (!data->var_death && data->num_meals_array[c])
	{
		if (ft_has_taken_fork(data, c, d))
			return ((void *)ft_return_routine(7));
		if (data->num_philos == 1)
			return ((void *)ft_return_routine \
			(pthread_mutex_unlock(&data->mutex_forks[d])));
		if ((ft_has_taken_fork(data, c, c)) || (ft_is_eating(data, c, d)) || \
				(ft_is_sleeping_and_is_thinking(data, c)))
			return ((void *)ft_return_routine(7));
		if (data->num_meals != -1)
			data->num_meals_array[c]--;
	}
	return ((void *)ft_return_routine(0));
}

void	*ft_control(void *arg)
{
	t_data			*data;
	unsigned int	c;
	unsigned int	r;

	data = (t_data *)arg;
	c = data->index_philo;
	while (!data->var_death)
	{	
		r = ft_time(data->tp);
		if ((r - data->last_meal[c]) >= data->time_to_die && !data->var_death)
		{
			if (pthread_mutex_lock(&data->mutex_death))
				return ((void *)ft_return_routine(8));
			data->var_death++;
			if (pthread_mutex_lock(&data->mutex_print))
				return ((void *)ft_return_routine(8));
			if (data->var_death == 1 && data->num_meals_array[c] != 0)
				printf("%u\t%d died\n", r, c + 1);
			if (pthread_mutex_unlock(&data->mutex_print) || \
				(pthread_mutex_unlock(&data->mutex_death)))
				return ((void *)ft_return_routine(8));
		}
		usleep(10);
	}
	return ((void *)ft_return_routine(0));
}

int	ft_has_taken_fork(t_data *data, unsigned int c, unsigned int d)
{
	if (pthread_mutex_lock(&data->mutex_forks[d]))
		return ((1));
	if (pthread_mutex_lock(&data->mutex_print))
		return ((1));
	if (!data->var_death)
		printf("%u\t%u has taken fork %u\n", \
			ft_time(data->tp), c + 1, d + 1);
	if (pthread_mutex_unlock(&data->mutex_print))
		return ((1));
	return (0);
}

int	ft_is_eating(t_data *data, unsigned int c, unsigned int d)
{
	if (pthread_mutex_lock(&data->mutex_print))
		return (1);
	data->last_meal[c] = ft_time(data->tp);
	if (!data->var_death)
		printf("%u\t%u is eating\n", data->last_meal[c], c + 1);
	if (pthread_mutex_unlock(&data->mutex_print))
		return (1);
	usleep(data->time_to_eat * MSEC);
	if (pthread_mutex_unlock(&data->mutex_forks[d]))
		return (1);
	if (pthread_mutex_unlock(&data->mutex_forks[c]))
		return (1);
	return (0);
}

int	ft_is_sleeping_and_is_thinking(t_data *data, unsigned int c)
{
	if (pthread_mutex_lock(&data->mutex_print))
		return (1);
	if (!data->var_death)
		printf("%u\t%u is sleeping\n", ft_time(data->tp), c + 1);
	if (pthread_mutex_unlock(&data->mutex_print))
		return (1);
	usleep(data->time_to_sleep * MSEC);
	if (pthread_mutex_lock(&data->mutex_print))
		return (1);
	if (!data->var_death)
		printf("%u\t%u is thinking\n", ft_time(data->tp), c + 1);
	if (pthread_mutex_unlock(&data->mutex_print))
		return (1);
	return (0);
}
