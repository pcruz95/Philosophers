/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcruz <pcruz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 13:51:30 by pcruz             #+#    #+#             */
/*   Updated: 2021/08/13 15:35:40 by pcruz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_data *data, int status)
{
	unsigned int	i;

	printf("Finished\n");
	free(data->thread_philo);
	free(data->thread_control);
	free(data->last_meal);
	free(data->num_meals_array);
	if (pthread_mutex_destroy(&data->mutex_death) || \
		pthread_mutex_destroy(&data->mutex_print))
		printf("Error pthread_mutex_destroy\n");
	i = 0;
	while (i < data->num_philos)
		if (pthread_mutex_destroy(&data->mutex_forks[i++]))
			printf("Error pthread_mutex_destroy\n");
	free(data->mutex_forks);
	return (status);
}

int	ft_exit_error(t_data *data, int status, char *s)
{
	printf("%s\n", s);
	if (data)
		return (ft_exit(data, status));
	return (status);
}

int	*ft_return_routine(int status)
{
	int	*ret;

	ret = NULL;
	if (status)
	{
		ret = (int *)malloc(sizeof(int));
		if (ret)
			*ret = status;
		printf("Error in routine\n");
	}
	return (ret);
}

int	ft_atoi(char *line, long *num)
{
	int	i;

	(*num) = 0;
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (1);
	while (line[i] && line[i] != ' ')
	{
		if ((line[i] < '0' || line[i] > '9'))
			return (1);
		(*num) = (line[i] - 48) + (10 * (*num));
		i++;
	}
	while (line[i])
		if (line[i++] != ' ')
			return (1);
	if ((*num) > LIMIT_UP_UINT)
		return (1);
	return (0);
}

unsigned int	ft_time(struct timeval tp)
{
	struct timeval	tp2;
	unsigned int	r;

	gettimeofday(&tp2, NULL);
	r = tp.tv_sec * MSEC + tp.tv_usec / MSEC;
	r = tp2.tv_sec * MSEC + tp2.tv_usec / MSEC - r;
	return (r);
}
