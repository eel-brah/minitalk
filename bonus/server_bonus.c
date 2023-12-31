/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:41 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/31 16:45:19 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

int	unicode_spr(int *byte, int *size)
{
	if (*byte == 0b11000000)
	{
		*size = 15 - (7 - *size);
		*byte <<= 8;
		return (2);
	}
	if (*byte == 0b11100000)
	{
		*size = 23 - (7 - *size);
		*byte <<= 16;
		return (3);
	}
	if (*byte == 0b11110000)
	{
		*size = 31 - (7 - *size);
		*byte <<= 24;
		return (4);
	}
	return (1);
}

void	setter(int *byte, int *size, int *w)
{
	*w = 0;
	*byte = 0;
	*size = 7;
}

void	print_bits(int *byte, int *size, int *w, pid_t cr_pid)
{
	char	c;

	if (*byte == 0)
	{
		write(1, "\n", 1);
		setter(byte, size, w);
		if (kill(cr_pid, SIGUSR1) == -1)
			ft_printf("Failed to send %d", SIGUSR1);
	}
	else
	{
		c = *byte >> 24;
		write(1, &c, 1);
		c = *byte >> 16;
		write(1, &c, 1);
		c = *byte >> 8;
		write(1, &c, 1);
		write(1, byte, 1);
	}
	setter(byte, size, w);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static pid_t	cr_pid;
	static int		byte;
	static int		size;
	static int		w;

	(void)context;
	if (cr_pid != info->si_pid)
	{
		setter(&byte, &size, &w);
		cr_pid = info->si_pid;
	}
	if (sig == SIGUSR2)
		byte |= (1 << size);
	if (!w && byte & 0b10000000 && size == 3)
		unicode_spr(&byte, &size);
	if (size == 0)
		print_bits(&byte, &size, &w, cr_pid);
	else
		size--;
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
		ft_printf("Failed to send %d", SIGUSR1);
		return (1);
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_printf("Failed to send %d", SIGUSR2);
		return (1);
	}
	ft_printf("PID: %i\n", getpid());
	while (1)
		pause();
	return (0);
}
