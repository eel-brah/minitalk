/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:05:41 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/30 01:35:22 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <libc.h>
#include "libft/libft.h"

// char	*bits_to_str(char *bits)
// {
// 	char	*str;
// 	size_t	size;
// 	int		i;
// 	int		j;

// 	size = ft_strlen(bits);
// 	size /= 8;
// 	str = ft_calloc(size + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	j = 1;
// 	while (*bits)
// 	{
// 		if (*bits == '1')
// 			str[i] = str[i] | (128 / j);
// 		j *= 2;
// 		bits++;
// 		if (j > 128)
// 		{
// 			j = 1;
// 			i++;
// 		}
// 	}
// 	str[i] = 0;
// 	return (str);
// }

// void	*str_realloc(char *ptr, size_t newSize)
// {
// 	char	*new;

// 	new = ft_calloc(newSize, sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	if (ptr)
// 		ft_strlcpy(new, ptr, newSize);
// 	free(ptr);
// 	return (new);
// }

typedef struct s_bit
{
	char	bit;
	int		count;
}	t_bit;

t_bit bit;

void handler(int sig, siginfo_t * info, void * context)
{
    if(sig == SIGUSR2)
       bit.bit |= (1 << bit.count);
	bit.count--;
	if (bit.count < 0)
	{
		if (bit.bit == 0)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
			bit.bit = 0;
			bit.count = 7;
			return ;
		}
		write(1, &bit.bit, 1);
		bit.bit = 0;
		bit.count = 7;
	}
	kill(info->si_pid, SIGUSR1);
}

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
	bit.bit = 0;
	bit.count = 7;
	while (1)
		pause();
}