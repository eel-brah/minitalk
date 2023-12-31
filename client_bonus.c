/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:45 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/31 02:19:38 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

char	*char_to_bits(char c)
{
	char	*p;
	int		i;

	p = malloc(9 * sizeof(char));
	if (!p)
		return (NULL);
	p[8] = 0;
	i = 0;
	while (i < 8)
	{
		if (c & 0b10000000)
			p[i] = '1';
		else
			p[i] = '0';
		c <<= 1;
		i++;
	}
	return (p);
}

void	*str_realloc(char *ptr, size_t newSize)
{
	char	*new;

	new = ft_calloc(newSize, sizeof(char));
	if (!new)
		return (NULL);
	if (ptr)
		ft_strlcpy(new, ptr, newSize);
	free(ptr);
	return (new);
}

void	*free_them(char *p1, char *p2)
{
	free(p1);
	free(p2);
	return (NULL);
}

char	*last_bit(char *bits, size_t size)
{
	char	*c;
	char	*tmp;

	c = char_to_bits(0);
	if (!c)
		return (free_them(c, bits));
	size += 8;
	tmp = str_realloc(bits, size);
	if (!tmp)
		return (free_them(c, bits));
	bits = tmp;
	ft_strlcat(bits, c, size);
	free(c);
	return (bits);
}

char	*str_to_bits(char *str)
{
	char	*c;
	char	*bits;
	char	*tmp;
	size_t	size;

	if (!str)
		return (NULL);
	bits = NULL;
	size = 1;
	while (*str)
	{
		c = char_to_bits(*str);
		if (!c)
			return (free_them(c, NULL));
		size += 8;
		tmp = str_realloc(bits, size);
		if (!tmp)
			return (free_them(c, bits));
		bits = tmp;
		ft_strlcat(bits, c, size);
		free(c);
		str++;
	}
	return (last_bit(bits, size));
}

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
	if (kill(pid, 0) == -1)
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
			ft_printf("g_done\n");
		p++;
	}
}

int	main(int argc, char **argv)// if enpty string
{
	char	*p;
	pid_t	pid;

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
	ft_printf("Sending: \"%s\" To %i\n", argv[2], pid);
	send_msg(p, pid);
	free(p);
	return (0);
}