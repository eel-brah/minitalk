/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:45 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/30 01:31:29 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libc.h>
#include "libft/libft.h"

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
		return (free_them(c, NULL));
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

int pauseIt;

void handler(int sig)
{
	if (sig == SIGUSR1)
		pauseIt = 0;
	if (sig == SIGUSR2)
		pauseIt = 2;
}

void is_pause()
{
	if (pauseIt == 1)
		pause();
	if (pauseIt == 2)
		ft_printf("DONE\n");
	pauseIt = 1;
}

int main(int argc, char **argv)
{
	char *p;
	char *s;
	pid_t pid;
	int sig;

	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return 1;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return 1;
pauseIt = 1;
	pid = atoi(argv[1]);
	s = argv[2];
	p = str_to_bits(s);
	if (!p)
		return 1;
	printf("Sending: \"%s\" To %i\n", p, pid);
	while (*p)
	{
		if (*p == '0')
			kill(pid, SIGUSR1);
		else if (*p == '1')
			kill(pid, SIGUSR2);
		is_pause();
		p++;
	}
}