/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmohamm <anmohamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:37:17 by anmohamm          #+#    #+#             */
/*   Updated: 2023/09/13 12:33:52 by anmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	check_signal(int signum, siginfo_t *info, void *context)
{
	static int	bit;
	static int	character;

	(void)context;
	if (signum == SIGUSR1)
		character = character | (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (character == 0)
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
			{
				ft_putstr("Error sending SIGUSR2\n");
				exit (1);
			}
		}
		else
			ft_putchar(character);
		bit = 0;
		character = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					pid;

	(void)ac;
	(void)av;
	pid = getpid();
	ft_putstr("PID :");
	ft_putnbr(pid);
	ft_putchar('\n');
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = check_signal;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
}
