/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:04:56 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/01/20 15:55:18 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static char c_buffer = 0;

	(void)context;
	if (signum == SIGUSR1)
		c_buffer |= (0 << bit);
	else if (signum == SIGUSR2)
		c_buffer |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", c_buffer);
		if (c_buffer == '\0')
			ft_printf("\n");
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
