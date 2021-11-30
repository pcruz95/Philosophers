/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcruz <pcruz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 13:14:14 by pcruz             #+#    #+#             */
/*   Updated: 2021/08/13 15:32:59 by pcruz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

# define LIMIT_UP_UINT 4294967295
# define MAX_N_THREADS 4095
# define SEC		1000000
# define MSEC	1000

typedef struct s_data
{
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			num_meals;
	struct timeval	tp;
	pthread_t		*thread_philo;
	pthread_t		*thread_control;
	unsigned int	index_philo;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_death;
	int				var_death;
	unsigned int	*last_meal;
	long int		*num_meals_array;
}					t_data;

unsigned int	ft_time(struct timeval tp);
void			*ft_control(void *arg);
int				ft_has_taken_fork(t_data *data, unsigned int c, unsigned int d);
int				ft_is_eating(t_data *data, unsigned int c, unsigned int d);
int				ft_is_sleeping_and_is_thinking(t_data *data, unsigned int c);
void			*ft_routine(void *arg);
int				ft_creating_threads(t_data *data);
int				ft_waiting_threads(t_data *data);
int				ft_init(t_data *data);
int				*ft_return_routine(int status);
int				ft_exit_error(t_data *data, int status, char *s);
int				ft_exit(t_data *data, int status);
int				ft_atoi(char *line, long *num);
int				ft_check_and_init_args(char **av, t_data *data);

#endif
