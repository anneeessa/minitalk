/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:28:45 by anmohamm          #+#    #+#             */
/*   Updated: 2023/09/13 12:29:36 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	check_message(int signum)
{
	if (signum == SIGUSR2)
	{
		ft_putstr("characters recieved successfully\n");
		exit(0);
	}
}

void	send_message(int pid, char *str)
{
	int	bit;
	int	i;

	bit = 7;
	i = 0;
	while (str[i])
	{
		while (bit >= 0)
		{
			if (str[i] & (1 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(1000);
			bit--;
		}
		i++;
		bit = 7;
	}
	bit = 8;
	while (bit--)
	{
		kill(pid, SIGUSR2);
		usleep(1000);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_putstr("error :wrong number of arguments\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, check_message);
	signal(SIGUSR2, check_message);
	if (pid < 0)
	{
		ft_putstr("invalid pid\n");
		return (1);
	}
	send_message(pid, av[2]);
}
