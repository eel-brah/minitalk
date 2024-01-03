/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:45 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/03 21:38:04 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	check_args(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("\033[0;31mUsage: %s PID message\033[0m\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_printf("\033[0;31mInvalid PID: %s\033[0m\n", argv[1]);
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
		p++;
	}
}

int	main(int argc, char **argv)
{
	char	*p;
	pid_t	pid;
	char	*dots;

	if (check_args(argc, argv))
		return (1);
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
	ft_printf("Sending: \033[0;34m\"%.15s%s\"\033[0m To \033[1;32m%i\033[0m\n",
		argv[2], dots, pid);
	send_msg(p, pid);
	free(p);
	return (0);
}
