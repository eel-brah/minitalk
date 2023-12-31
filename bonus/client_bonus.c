/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:45 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/31 17:03:58 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"

volatile sig_atomic_t	g_done;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_done = 1;
}

int	sig_catch(void)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
		ft_putendl_fd("Error: sigaction SIGUSR1 faild", 2);
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s PID message\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_printf("Invalid PID: %s\n", argv[1]);
		return (1);
	}
	return (0);
}

void	send_msg(char *p, pid_t pid)
{
	while (*p)
	{
		if (*p == '0')
			kill(pid, SIGUSR1);
		else if (*p == '1')
			kill(pid, SIGUSR2);
		usleep(200);
		if (g_done == 1)
			ft_printf("The message has been received\n");
		p++;
	}
}

int	main(int argc, char **argv)// if enpty string
{
	char	*p;
	pid_t	pid;
	char	*dots;

	if (sig_catch() || check_args(argc, argv))
		return (1);
	g_done = 0;
	pid = ft_atoi(argv[1]);
	p = str_to_bits(argv[2]);
	if (!p)
	{
		ft_putendl_fd("Error: malloc", 2);
		return (1);
	}
	dots = "";
	if (ft_strlen(argv[2]) > 15)
		dots = "...";
	ft_printf("Sending: \"%.15s%s\" To %i\n", argv[2], dots, pid);
	send_msg(p, pid);
	free(p);
	return (0);
}
