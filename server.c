/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:41 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/31 00:27:23 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_byte	byte;

void handler(int sig, siginfo_t *info, void *context)
{
	static pid_t	cr_pid;
	static int		byte = 0;
	static int		size = 7;

	if (cr_pid != info->si_pid)
	{
		byte = 0;
		size = 7;
		cr_pid = info->si_pid;
	}
    if(sig == SIGUSR2)
       byte |= (1 << size);
	if (size == 0)
	{
		if (byte == 0)
			write(1, "\n", 1);
		else
			write(1, &byte, 1);
		byte = 0;
		size = 7;
	}
	else 
		size--;
}

int main(int argc, char **argv)
{
	struct sigaction	act;

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
