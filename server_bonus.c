/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:41 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/31 01:12:00 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_byte	byte;

void print_bits(int c)
{
	int		i;

	i = 0;
	while (i < 24)
	{
		if (c & 0b100000000000000000000000)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		c <<= 1;
		i++;
	}
}

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

void handler(int sig, siginfo_t *info, void *context)
{
	static pid_t cr_pid;
	static int		byte = 0;
	static int		size = 7;
	static int w;

	if (cr_pid != info->si_pid)
	{
		w = 0;
		byte = 0;
		size = 7;
		cr_pid = info->si_pid;
	}
    if(sig == SIGUSR2)
       byte |= (1 << size);
	if (!w && byte & 0b10000000 && size == 3)
		unicode_spr(&byte, &size);
	if (size == 0)
	{
		if (byte == 0)
		{
			write(1, "\n", 1);
			byte = 0;
			size = 7;
			w = 0;
			if (kill(cr_pid, SIGUSR1) == -1)
				ft_printf("Failed to send SIGUSR1");
		}
		else
		{
			char c = byte >> 24;
			write(1, &c, 1);
			c = byte >> 16;
			write(1, &c, 1);
			c = byte >> 8;
			write(1, &c, 1);
			write(1, &byte, 1);
		}
		w = 0;
		byte = 0;
		size = 7;
	}
	else
		size--;
}

// unicode 2 : 1100 
// unicode 3 : 1110 
// unicode 4 : 1111 

int main(int argc, char **argv)
{
	struct sigaction act;
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART | SA_SIGINFO;

	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return 1;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return 1;
	printf("%i\n", getpid());
	while (1)
		pause();
	return (0);
}
