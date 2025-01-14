/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrito-s <cbrito-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:04:47 by cbrito-s          #+#    #+#             */
/*   Updated: 2025/01/14 15:33:08 by cbrito-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

server_confirm = 0;

static void	ft_handler(int signum)
{
	if (signum == SIGUSR1)
		server_confirm = 1;
}

static void	ft_send_message_bit(int pid, char *str)
{
	while (*str != '\0')
	{
		if (*str == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		str++;
		while(!server_confirm)
			;
		server_confirm = 0;
	}
}

static char	*ft_bit(char *str, int len)
{
	int		i;
	int		j;
	int		c;
	int		bit;
	char	*ret;

	i = 0;
	j = 0;
	ret = ft_calloc(len * 8 + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		c = str[i++];
		bit = 8;
		while (bit > 0)
		{
			if (c & (1 << (bit-- - 1)))
				ret[j] = '1';
			else
				ret[j] = '0';
			j++;
		}
	}
	return (ret);
}

int	main(int ac, char **av)
{
	int		pid;
	char	*bit;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		signal(SIGUSR1, ft_handler);
		bit = ft_bit(av[2], ft_strlen(av[2]));
		ft_send_message_bit(pid, bit);
	}
	else
		ft_printf("Usage: ./client [PID] [message]\n");
	return (0);
}
