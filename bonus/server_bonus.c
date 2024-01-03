/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:41 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/03 21:40:05 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

void	unicode_spr(int *byte, int *size)
{
	if (*byte == 0b11000000)
	{
		*size = 15 - (7 - *size);
		*byte <<= 8;
		return ;
	}
	if (*byte == 0b11100000)
	{
		*size = 23 - (7 - *size);
		*byte <<= 16;
		return ;
	}
	if (*byte == 0b11110000)
	{
		*size = 31 - (7 - *size);
		*byte <<= 24;
		return ;
	}
	return ;
}

void	setter(int *byte, int *size)
{
	*byte = 0;
	*size = 7;
}

void	print_bits(int *byte, int *size, pid_t cr_pid)
{
	char	c;

	if (*byte == 0)
	{
		write(1, "\n", 1);
		setter(byte, size);
		if (kill(cr_pid, SIGUSR1) == -1)
			ft_printf("\033[0;31mFailed to send %d\033[0m\n", SIGUSR1);
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
	setter(byte, size);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static pid_t	cr_pid;
	static int		byte;
	static int		size;

	(void)context;
	if (cr_pid != info->si_pid)
	{
		setter(&byte, &size);
		cr_pid = info->si_pid;
	}
	if (sig == SIGUSR2)
		byte |= (1 << size);
	if (byte & 0b10000000 && size == 3)
		unicode_spr(&byte, &size);
	if (size == 0)
		print_bits(&byte, &size, cr_pid);
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
		ft_printf("\033[0;31mFailed to send %d\033[0m\n", SIGUSR1);
		return (1);
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_printf("\033[0;31mFailed to send %d\033[0m\n", SIGUSR2);
		return (1);
	}
	ft_printf("PID: \033[1;32m%i\033[0m\n", getpid());
	while (1)
		pause();
	return (0);
}
