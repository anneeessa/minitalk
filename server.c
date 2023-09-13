/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:37:33 by anmohamm          #+#    #+#             */
/*   Updated: 2023/08/28 16:50:55 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig)
{
	static int	bit;
	static int	character;

	if (sig == SIGUSR1)
		character = character | (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		ft_putchar(character);
		bit = 0;
		character = 0;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	(void)av;
	if (ac != 1)
	{
		ft_putstr("error: invalid  no of argument\n");
		return (1);
	}
	pid = getpid();
	ft_putstr("PID :");
	ft_putnbr(pid);
	ft_putchar('\n');
	while (ac == 1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
}
