/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:04:56 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/01/14 17:42:09 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit;
	static char c_buffer;

	bit = 0;
	c_buffer = 0;
	(void)context;
	if (signum ==  SIGUSR1)
		c_buffer |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c_buffer);
		bit = 0;
		c_buffer = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
