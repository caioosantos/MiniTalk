/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:04:47 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/01/20 15:55:17 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	server_confirm = 0;

static void	ft_handler(int signum)
{
	if (signum == SIGUSR1)
		server_confirm = 1;
}

static void	ft_send_message(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit++;
		while (!server_confirm)
			;
		server_confirm = 0;
	}
}

static void	ft_send_end(int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		kill(pid, SIGUSR1);
		bit++;
		while (!server_confirm)
			;
		server_confirm = 0;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		signal(SIGUSR1, ft_handler);
		while (*av[2])
		{
			ft_send_message(pid, *av[2]);
			av[2]++;
		}
		ft_send_end(pid);
	}
	else
		ft_printf("Usage: ./client [PID] [message]\n");
	return (0);
}
